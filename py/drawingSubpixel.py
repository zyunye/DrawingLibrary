import math

import cv2
from numpy.typing import NDArray

from DrawingLibrary.py.drawingDefs import COLOR_GREEN, POINT_RADIUS, COLOR_BLUE


class SubpixelWorkspace:
    def __init__(self, img: NDArray, row: float, col: float, scale: int, buffer: int):
        self.zoomScale = scale
        self.buffer = buffer
        self.retTemp = False

        leftR = row - buffer
        leftC = col - buffer
        rightR = row + buffer
        rightC = col + buffer

        imgShape = img.shape
        imgHeight = imgShape[0]
        imgWidth = imgShape[1]
        minExtent = min(leftR, leftC)

        # Non throwing bounds enforcement. Will compress the buffer to fit within the confines of the image silently.
        if minExtent < 0 or rightC >= imgWidth or rightR >= imgHeight:
            differences = []

            if leftR < 0:
                differences.append(buffer - abs(leftR))
            if rightR >= imgHeight:
                differences.append(buffer - (rightR - imgHeight))
            if leftC < 0:
                differences.append(buffer - abs(leftC))
            if rightC >= imgWidth:
                differences.append(buffer - (rightC - imgWidth))

            absDiff = int(min(differences))

            leftR = row - absDiff
            leftC = col - absDiff
            rightR = row + absDiff
            rightC = col + absDiff

        leftR = round(leftR)
        leftC = round(leftC)
        rightR = round(rightR)
        rightC = round(rightC)

        self.zoomedImage = img[leftR:rightR, leftC:rightC]
        self.zoomedImage = cv2.resize(self.zoomedImage, fx=scale, fy=scale, interpolation=cv2.INTER_NEAREST)
        self.leftRow = leftR
        self.leftColumn = leftC
        self.temporaryImg = self.zoomedImage.copy()

    def drawCircle(self, row: float, col: float, radius: float, color=COLOR_GREEN, temp=False):
        zoomedRow = int(round((row - self.leftRow) * self.zoomScale + self.zoomScale / 2.0))
        zoomedCol = int(round((col - self.leftColumn) * self.zoomScale + self.zoomScale / 2.0))
        zoomedRadius = int(round(radius * self.zoomScale))

        if temp:
            if not self.retTemp:
                self.temporaryImg = self.zoomedImage.copy()
                self.retTemp = True
            cv2.circle(self.temporaryImg, (zoomedCol, zoomedRow), zoomedRadius, color)
        else:
            cv2.circle(self.zoomedImage, (zoomedCol, zoomedRow), zoomedRadius, color)

    def drawPoint(self, row: float, col: float, color=COLOR_GREEN, temp=False):
        zoomedRow = int(round((row - self.leftRow) * self.zoomScale + self.zoomScale / 2.0))
        zoomedCol = int(round((col - self.leftColumn) * self.zoomScale + self.zoomScale / 2.0))

        if temp:
            if not self.retTemp:
                self.temporaryImg = self.zoomedImage.copy()
                self.retTemp = True
            cv2.circle(self.temporaryImg, (zoomedCol, zoomedRow), POINT_RADIUS, color, -1)
        else:
            cv2.circle(self.zoomedImage, (zoomedCol, zoomedRow), POINT_RADIUS, color, -1)

    def drawLine(self, rowStart: float, colStart: float, rowEnd: float, colEnd: float, color=COLOR_GREEN, temp=False):
        zoomedRowStart = int(round((rowStart - self.leftRow) * self.zoomScale + self.zoomScale / 2.0))
        zoomedColStart = int(round((colStart - self.leftColumn) * self.zoomScale + self.zoomScale / 2.0))
        zoomedRowEnd = int(round((rowEnd - self.leftRow) * self.zoomScale + self.zoomScale / 2.0))
        zoomedColEnd = int(round((colEnd - self.leftColumn) * self.zoomScale + self.zoomScale / 2.0))

        if temp:
            if not self.retTemp:
                self.temporaryImg = self.zoomedImage.copy()
                self.retTemp = True
            cv2.line(self.temporaryImg, (zoomedColStart, zoomedRowStart), (zoomedColEnd, zoomedRowEnd), color)
        else:
            cv2.line(self.zoomedImage, (zoomedColStart, zoomedRowStart), (zoomedColEnd, zoomedRowEnd), color)

    def drawRect(self, corners, color=COLOR_GREEN, temp=False, drawCorners=False):
        for i in range(len(corners) - 1):
            rowStart = corners[i][1]
            colStart = corners[i][0]
            rowEnd = corners[i + 1][1]
            colEnd = corners[i + 1][0]
            self.drawLine(rowStart, colStart, rowEnd, colEnd, color=color, temp=temp)
        rowStart = corners[-1][1]
        colStart = corners[-1][0]
        rowEnd = corners[0][1]
        colEnd = corners[0][0]
        self.drawLine(rowStart, colStart, rowEnd, colEnd, color=color, temp=temp)

        if drawCorners:
            self.drawCircle(corners[0][1], corners[0][0], 5, COLOR_BLUE, temp=temp)
            self.drawCircle(corners[1][1], corners[1][0], 5, COLOR_BLUE, temp=temp)
            self.drawCircle(corners[2][1], corners[2][0], 5, COLOR_BLUE, temp=temp)
            self.drawCircle(corners[3][1], corners[3][0], 5, COLOR_BLUE, temp=temp)

    def drawEllipse(self, row, col, phi, shortRadius, longRadius, color=COLOR_GREEN, temp=False):
        zoomedRow = int(round((row - self.leftRow) * self.zoomScale + self.zoomScale / 2.0))
        zoomedCol = int(round((col - self.leftColumn) * self.zoomScale + self.zoomScale / 2.0))
        zoomedShortRad = int(round(shortRadius * self.zoomScale))
        zoomedLongRad = int(round(longRadius * self.zoomScale))

        if temp:
            if not self.retTemp:
                self.temporaryImg = self.zoomedImage.copy()
                self.retTemp = True
            cv2.ellipse(self.temporaryImg, (zoomedCol, zoomedRow), (zoomedShortRad, zoomedLongRad),
                        -phi * 180 / math.pi, 0, 360, color)
        else:
            cv2.ellipse(self.zoomedImage, (zoomedCol, zoomedRow), (zoomedShortRad, zoomedLongRad), -phi * 180 / math.pi,
                        0, 360, color)

    def getZoomedImage(self):
        if self.retTemp:
            self.retTemp = False
            return self.temporaryImg
        return self.zoomedImage
