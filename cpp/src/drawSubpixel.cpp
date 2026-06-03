#include "drawSubpixel.hpp"

using namespace cv;

SubpixelWorkspace::SubpixelWorkspace(const cv::Mat &img, double row, double col, int scale, int buffer)
        : zoomScale{scale},
          buffer{buffer},
          retTemp(false) {
    double leftR = row - buffer;
    double leftC = col - buffer;
    double rightR = row + buffer;
    double rightC = col + buffer;

    Size imgShape = img.size();
    double minExtent = std::min({leftR, leftC});

    // Non throwing bounds enforcement. Will compress the buffer to fit within the confines of the image silently.
    if (minExtent < 0 || rightC >= imgShape.width || rightR >= imgShape.height) {
        std::vector<double> differences;

        if (leftR < 0) {
            differences.push_back(buffer - abs(leftR));
        }

        if (rightR >= imgShape.height) {
            differences.push_back(buffer - (rightR - imgShape.height));
        }
        if (leftC < 0) {
            differences.push_back(buffer - abs(leftC));
        }

        if (rightC >= imgShape.width) {
            differences.push_back(buffer - (rightC - imgShape.width));
        }

        int absDiff = (int) *std::min_element(differences.begin(), differences.end());

        leftR = row - absDiff;
        leftC = col - absDiff;
        rightR = row + absDiff;
        rightC = col + absDiff;

        // std::cout << imgShape << "\n";
        // std::cout << leftC << " " << leftR << "\n";
        // std::cout << rightC << " " << rightR << "\n";
        // std::cout << differences << "\n";
        // std::cout << absDiff << "\n";
    }

    // UNCOMMENT FOR BOUNDS DEBUGGING
    // rectangle(img,
    //           Point2d(col - buffer, row - buffer),
    //           Point2d(col + buffer, row + buffer),
    //           Scalar(0, 255, 0));
    // rectangle(img,
    //           Point2d(leftC, leftR),
    //           Point2d(rightC, rightR),
    //           Scalar(0, 255, 0));

    leftR = round(leftR);
    leftC = round(leftC);
    rightR = round(rightR);
    rightC = round(rightC);

    Range rowRange = Range(int(leftR), int(rightR));
    Range colRange = Range(int(leftC), int(rightC));

    constexpr InterpolationFlags INTERPOLATION = INTER_NEAREST;

    zoomedImage = img(rowRange, colRange);
    resize(zoomedImage, zoomedImage, Size(), scale, scale, INTERPOLATION);
    leftRow = int(leftR);
    leftColumn = int(leftC);
    temporaryImg = zoomedImage.clone();
}

void SubpixelWorkspace::drawCircle(double row, double col, double radius, const cv::Scalar &color) {
    int zoomedRow = int(round((row - leftRow) * zoomScale + zoomScale / 2.0));
    int zoomedCol = int(round((col - leftColumn) * zoomScale + zoomScale / 2.0));
    int zoomedRadius = int(round(radius * zoomScale));

    circle(zoomedImage, Point2d(zoomedCol, zoomedRow), zoomedRadius, color);
}

void SubpixelWorkspace::drawTempCircle(double row, double col, double radius, const cv::Scalar &color) {
    int zoomedRow = int(round((row - leftRow) * zoomScale + zoomScale / 2.0));
    int zoomedCol = int(round((col - leftColumn) * zoomScale + zoomScale / 2.0));
    int zoomedRadius = int(round(radius * zoomScale));

    if (not retTemp) {
        temporaryImg = zoomedImage.clone();
        retTemp = true;
    }
    circle(temporaryImg, Point2d(zoomedCol, zoomedRow), zoomedRadius, color);
}

void SubpixelWorkspace::drawPoint(double row, double col, const cv::Scalar &color) {
    constexpr int POINT_RADIUS = 3;

    int zoomedRow = int(round((row - leftRow) * zoomScale + zoomScale / 2.0));
    int zoomedCol = int(round((col - leftColumn) * zoomScale + zoomScale / 2.0));

    circle(zoomedImage, Point2d(zoomedCol, zoomedRow), POINT_RADIUS, color, -1);
}

void SubpixelWorkspace::drawTempPoint(double row, double col, const cv::Scalar &color) {
    constexpr int POINT_RADIUS = 3;

    int zoomedRow = int(round((row - leftRow) * zoomScale + zoomScale / 2.0));
    int zoomedCol = int(round((col - leftColumn) * zoomScale + zoomScale / 2.0));

    if (not retTemp) {
        temporaryImg = zoomedImage.clone();
        retTemp = true;
    }
    circle(temporaryImg, Point2d(zoomedCol, zoomedRow), POINT_RADIUS, color, -1);
}

void SubpixelWorkspace::drawLine(double rowStart, double colStart, double rowEnd, double colEnd, const cv::Scalar &color) {
    int zoomedRowStart = int(round((rowStart - leftRow) * zoomScale + zoomScale / 2.0));
    int zoomedColStart = int(round((colStart - leftColumn) * zoomScale + zoomScale / 2.0));
    int zoomedRowEnd = int(round((rowEnd - leftRow) * zoomScale + zoomScale / 2.0));
    int zoomedColEnd = int(round((colEnd - leftColumn) * zoomScale + zoomScale / 2.0));

    line(zoomedImage, Point2d(zoomedColStart, zoomedRowStart), Point2d(zoomedColEnd, zoomedRowEnd), color);
}

void SubpixelWorkspace::drawTempLine(double rowStart, double colStart, double rowEnd, double colEnd, const cv::Scalar &color) {
    int zoomedRowStart = int(round((rowStart - leftRow) * zoomScale + zoomScale / 2.0));
    int zoomedColStart = int(round((colStart - leftColumn) * zoomScale + zoomScale / 2.0));
    int zoomedRowEnd = int(round((rowEnd - leftRow) * zoomScale + zoomScale / 2.0));
    int zoomedColEnd = int(round((colEnd - leftColumn) * zoomScale + zoomScale / 2.0));

    if (not retTemp) {
        temporaryImg = zoomedImage.clone();
        retTemp = true;
    }
    line(temporaryImg, Point2d(zoomedColStart, zoomedRowStart), Point2d(zoomedColEnd, zoomedRowEnd), color);
}

void SubpixelWorkspace::drawRect(const std::vector<cv::Point2d> &corners, const cv::Scalar &color, bool drawCorners) {
    double rowStart;
    double colStart;
    double rowEnd;
    double colEnd;

    for (size_t i = 0; i < corners.size() - 1; i++) {
        rowStart = corners[i].x;
        colStart = corners[i].y;
        rowEnd = corners[i + 1].x;
        colEnd = corners[i + 1].y;

        drawLine(rowStart, colStart, rowEnd, colEnd, color);
    }
    rowStart = corners[3].x;
    colStart = corners[3].y;
    rowEnd = corners[0].x;
    colEnd = corners[0].y;

    drawLine(rowStart, colStart, rowEnd, colEnd, color);

    if (drawCorners) {
        drawCircle(corners[0].x, corners[0].y, 5, COLOR_BLUE);
        drawCircle(corners[1].x, corners[1].y, 5, COLOR_GREEN);
        drawCircle(corners[2].x, corners[2].y, 5, COLOR_RED);
        drawCircle(corners[3].x, corners[3].y, 5, COLOR_WHITE);
    }
}

void SubpixelWorkspace::drawTempRect(const std::vector<cv::Point2d> &corners, const cv::Scalar &color, bool drawCorners) {
    double rowStart;
    double colStart;
    double rowEnd;
    double colEnd;

    for (size_t i = 0; i < corners.size() - 1; i++) {
        rowStart = corners[i].x;
        colStart = corners[i].y;
        rowEnd = corners[i + 1].x;
        colEnd = corners[i + 1].y;

        drawTempLine(rowStart, colStart, rowEnd, colEnd, color);
    }
    rowStart = corners[3].x;
    colStart = corners[3].y;
    rowEnd = corners[0].x;
    colEnd = corners[0].y;

    drawTempLine(rowStart, colStart, rowEnd, colEnd, color);

    if (drawCorners) {
        drawTempCircle(corners[0].x, corners[0].y, 5, COLOR_BLUE);
        drawTempCircle(corners[1].x, corners[1].y, 5, COLOR_GREEN);
        drawTempCircle(corners[2].x, corners[2].y, 5, COLOR_RED);
        drawTempCircle(corners[3].x, corners[3].y, 5, COLOR_WHITE);
    }
}

void SubpixelWorkspace::drawEllipse(double row, double col, double phi, double shortRadius, double longRadius,
                                    const cv::Scalar &color) {
    int zoomedRow = int(round((row - leftRow) * zoomScale + zoomScale / 2.0));
    int zoomedCol = int(round((col - leftColumn) * zoomScale + zoomScale / 2.0));
    int zoomedShortRad = int(round(shortRadius * zoomScale));
    int zoomedLongRad = int(round(longRadius * zoomScale));

    ellipse(zoomedImage, Point2d(zoomedCol, zoomedRow), Size(zoomedShortRad, zoomedLongRad), (-phi) * 180 / CV_PI, 0, 360, color);
}

void SubpixelWorkspace::drawTempEllipse(double row, double col, double phi, double shortRadius, double longRadius,
                                        const cv::Scalar &color) {
    int zoomedRow = int(round((row - leftRow) * zoomScale + zoomScale / 2.0));
    int zoomedCol = int(round((col - leftColumn) * zoomScale + zoomScale / 2.0));
    int zoomedShortRad = int(round(shortRadius * zoomScale));
    int zoomedLongRad = int(round(longRadius * zoomScale));

    if (not retTemp) {
        temporaryImg = zoomedImage.clone();
        retTemp = true;
    }
    ellipse(temporaryImg, Point2d(zoomedCol, zoomedRow), Size(zoomedShortRad, zoomedLongRad), (-phi) * 180 / CV_PI, 0, 360, color);
}


