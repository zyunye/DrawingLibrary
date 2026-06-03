#include "drawHandles.hpp"

using namespace cv;

void SubpixelMeasureWorkspace::drawMeasureHandle(RectangleElement &measure, const cv::Scalar &color, const bool drawCorners) {
    std::vector<Point2d> corners = measure.getCornerPoints();

    double rectRow = measure.getRow();
    double rectCol = measure.getColumn();

    for (int i = 0; i < corners.size(); i++) {
        corners[i] += Point2d(rectRow, rectCol);
    }

    drawRect(corners, color, drawCorners);
}

void SubpixelMeasureWorkspace::drawMeasureHandle(ArcElement &measure, const cv::Scalar &color) {
    double row = measure.getRow();
    double col = measure.getColumn();
    double innerRad = measure.getInnerRadius();
    double outerRad = measure.getRadius();

    drawCircle(row, col, innerRad, color);
    drawCircle(row, col, outerRad, color);
}

void SubpixelMeasureWorkspace::drawMeasureHandle(ArcTransposedElement &measure, const cv::Scalar &color) {
    double row = measure.getRow();
    double col = measure.getColumn();
    double innerRad = measure.getInnerRadius();
    double outerRad = measure.getRadius();

    drawCircle(row, col, innerRad, color);
    drawCircle(row, col, outerRad, color);
}

void drawMeasureHandle(Mat &img, const RectangleElement &measureHandle, const Scalar &color, const bool drawCorners) {
    // Get the four points of the rectangle as (r, c) coordinates (before adjusting for center of measureHandle)
    std::vector<Point2d> rectPoints = measureHandle.getCornerPoints();

    for (Point2d &point : rectPoints) {
        // Adjust for center of measureHandle
        point.x += measureHandle.getRow();
        point.y += measureHandle.getColumn();

        // Swap row and column because openCV's drawing functions accept points in (col, row) order
        std::swap(point.x, point.y);
    }

    Point2d rect0 = rectPoints[0];
    Point2d rect1 = rectPoints[1];
    Point2d rect2 = rectPoints[2];
    Point2d rect3 = rectPoints[3];

    line(img, rect0, rect1, color, 1, LINE_AA);
    line(img, rect1, rect2, color, 1, LINE_AA);
    line(img, rect2, rect3, color, 1, LINE_AA);
    line(img, rect3, rect0, color, 1, LINE_AA);
    circle(img, Point2d(measureHandle.getColumn(), measureHandle.getRow()), 1, COLOR_RED, -1, LINE_AA);

    constexpr int RADIUS = 3;

    if (drawCorners) {
        circle(img, rect0, RADIUS, COLOR_BLUE, 1, LINE_AA);
        circle(img, rect1, RADIUS, COLOR_GREEN, 1, LINE_AA);
        circle(img, rect2, RADIUS, COLOR_RED, 1, LINE_AA);
        circle(img, rect3, RADIUS, COLOR_BLACK, 1, LINE_AA);
    }
}

void drawMeasureHandle(Mat &img, const ArcElement &measureHandle, const Scalar &color) {
    int r = measureHandle.getRow();
    int c = measureHandle.getColumn();
    int radius = measureHandle.getRadius();
    int innerRad = measureHandle.getInnerRadius();
    double angleStart = measureHandle.getAngleStart();
    double angleEnd = measureHandle.getAngleExtent();

    int xStart = c + int(round(radius * cos(angleStart)));
    int yStart = r - int(round(radius * sin(angleStart)));

    int xEnd = c + int(round(radius * cos(angleEnd)));
    int yEnd = r - int(round(radius * sin(angleEnd)));

    Point2d center(c, r);

    circle(img, center, radius, color, 1, LINE_AA);
    circle(img, center, innerRad, color, 1, LINE_AA);
    line(img, center, Point2d(xStart, yStart), color, 1, LINE_AA);
    line(img, center, Point2d(xEnd, yEnd), COLOR_RED, 1, LINE_AA);
}

void drawMeasureHandle(Mat &img, const ArcTransposedElement &measureHandle, const Scalar &color) {
    int r = measureHandle.getRow();
    int c = measureHandle.getColumn();
    int radius = measureHandle.getRadius();
    int innerRad = measureHandle.getInnerRadius();
    double angleStart = measureHandle.getAngleStart();
    double angleEnd = angleStart + measureHandle.getAngleExtent();

    int xStart = c + int(round(radius * cos(angleStart)));
    int yStart = r - int(round(radius * sin(angleStart)));

    int xEnd = c + int(round(radius * cos(angleEnd)));
    int yEnd = r - int(round(radius * sin(angleEnd)));

    Point2d center(c, r);

    circle(img, center, radius, color, 1, LINE_AA);
    circle(img, center, innerRad, color, 1, LINE_AA);
    line(img, center, Point2d(xStart, yStart), color, 1, LINE_AA);
    line(img, center, Point2d(xEnd, yEnd), COLOR_RED, 1, LINE_AA);
}