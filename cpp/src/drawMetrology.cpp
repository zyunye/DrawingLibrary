#include "drawMetrology.hpp"

#include "drawHandles.hpp"
#include "mathutils.hpp"

using namespace cv;

Point2i toCartesian(double radius, double theta) {
    int row = int(radius * cos(theta));
    int col = int(radius * sin(theta));

    return {col, row};
}

Point2i findEndpoint(const EllipseObject &obj, double angle) {
    // Calculate x, y coordinates based on the parametric angle
    double x = obj.getLongRadius() * cos(angle);
    double y = obj.getShortRadius() * sin(angle);

    // Rotate x, y by phi
    rotate(x, y, sin(obj.getPhi()), cos(obj.getPhi()));

    // Adjust to center of ellipse
    int c = int(x + obj.getColumn());
    int r = int(-y + obj.getRow());

    return {c, r};
}


void SubpixelMetrologyWorkspace::drawMetrology(ArcObject &obj, const cv::Scalar &color) {
    double row = obj.getRow();
    double col = obj.getColumn();
    double rad = obj.getRadius();

    drawCircle(row, col, rad, color);
}

void SubpixelMetrologyWorkspace::drawMetrology(EllipseObject &obj, const cv::Scalar &color) {
    double row = obj.getRow();
    double col = obj.getColumn();
    double phi = obj.getPhi();
    double shortRad = obj.getShortRadius();
    double longRad = obj.getLongRadius();

    drawEllipse(row, col, phi, shortRad, longRad, color);
}

void SubpixelMetrologyWorkspace::drawMetrology(LineObject &obj, const cv::Scalar &color) {
    double startRow = obj.getRowStart();
    double startCol = obj.getColumnStart();
    double endRow = obj.getRowEnd();
    double endCol = obj.getColumnEnd();

    drawLine(startRow, startCol, endRow, endCol, color);
}

void SubpixelMetrologyWorkspace::drawMetrology(RectObject &obj, const cv::Scalar &color, const bool drawCorners) {
    const std::vector<Point2d> &corners = obj.getRectPoints();

    drawRect(corners, color, drawCorners);
}


void drawArcObject(Mat &img, const ArcObject &obj, const Scalar &color) {
    Point2i center{obj.getColumn(), obj.getRow()};

    circle(img, center, obj.getRadius(), color, 1, LINE_AA);

    // Draw lines from center of circle to perimeter to represent angleStart and angleExtent
    double angleStart = obj.getAngleStart() + boost::math::double_constants::half_pi;
    double angleEnd = angleStart + obj.getAngleExtent();

    line(img, center, toCartesian(obj.getRadius(), angleStart) + center, COLOR_RED, 1, LINE_AA);
    line(img, center, toCartesian(obj.getRadius(), angleEnd) + center, COLOR_CYAN, 1, LINE_AA);

    for (const auto &measure : obj.getMeasures())
        drawMeasureHandle(img, measure, COLOR_ORANGE);
}

void drawEllipseObject(cv::Mat &img, const EllipseObject &obj, const cv::Scalar &color) {
    // Draw the elliptical arc
    Point2i center{obj.getColumn(), obj.getRow()};
    Size2i axes{obj.getLongRadius(), obj.getShortRadius()};

    double angleStart = obj.getAngleStart();
    double angleEnd = angleStart + obj.getAngleExtent();

    ellipse(img, center, axes, rad2deg(-obj.getPhi()), rad2deg(-angleStart), rad2deg(-angleEnd), color, 1, LINE_AA);

    // Draw the lines to represent angleStart and angleExtent
    line(img, center, findEndpoint(obj, angleStart), COLOR_RED, 1, LINE_AA);
    line(img, center, findEndpoint(obj, angleEnd), COLOR_CYAN, 1, LINE_AA);

    for (const auto &measure : obj.getMeasures())
        drawMeasureHandle(img, measure, COLOR_ORANGE);
}

void drawRectObject(cv::Mat &img, const RectObject &obj, const cv::Scalar &color, const bool drawCorners) {
    std::vector<MeasureRectangle> measures = obj.getMeasures();
    std::vector<Point2d> corners = obj.getRectPoints();

    for (int i = 0; i < corners.size() - 1; i++) {
        Point2d current = reverse(corners[i]);
        Point2d next = reverse(corners[i + 1]);

        line(img, current, next, color, 1, LINE_AA);
    }

    Point2d bottomLeft = reverse(corners[3]);
    Point2d bottomRight = reverse(corners[0]);
    line(img, bottomLeft, bottomRight, color, 1, LINE_AA);

    for (MeasureRectangle m : measures) {
        drawMeasureHandle(img, m, COLOR_ORANGE);
    }

    if (drawCorners) {
        circle(img, reverse(corners[0]), 3, COLOR_BLUE, -1, LINE_AA);
        circle(img, reverse(corners[1]), 3, COLOR_GREEN, -1, LINE_AA);
        circle(img, reverse(corners[2]), 3, COLOR_RED, -1, LINE_AA);
        circle(img, reverse(corners[3]), 3, COLOR_WHITE, -1, LINE_AA);
    }
}

void drawLineObject(cv::Mat &img, const LineObject &obj, const cv::Scalar &color, const bool drawEndPoints) {
    std::vector<MeasureRectangle> measures = obj.getMeasures();

    int startRow = obj.getRowStart();
    int startCol = obj.getColumnStart();
    int endRow = obj.getRowEnd();
    int endCol = obj.getColumnEnd();

    Point2d startPoint = Point2d(startCol, startRow);
    Point2d endPoint = Point2d(endCol, endRow);

    line(img, startPoint, endPoint, color, 1, LINE_AA);

    for (MeasureRectangle m : measures) {
        drawMeasureHandle(img, m, COLOR_ORANGE);
    }

    if (drawEndPoints) {
        circle(img, startPoint, 3, COLOR_BLUE, -1, LINE_AA);
        circle(img, endPoint, 3, COLOR_RED, -1, LINE_AA);
    }
}
