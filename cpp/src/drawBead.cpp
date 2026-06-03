#include "drawBead.hpp"

#include "mathutils.hpp"

using namespace cv;

inline double square(double x) {
    return x * x;
}

inline double getDistance(const Point2d &start, const Point2d &end) {
    return sqrt(square(end.x - start.x) + square(end.y - start.y));
}

inline double getAngle(const Point2d &p1, const Point2d &p2) {
    return atan2(p2.y - p1.y, p2.x - p1.x);
}

Contour getSurroundingContour(const BeadModel& beadModel, int halfWidth) {
    if (beadModel.beadContour.empty())
        return Contour{};

    Contour lowerContour;
    Contour upperContour;

    lowerContour.reserve(beadModel.beadContour.size());
    upperContour.reserve(beadModel.beadContour.size());

    for (size_t i = 1; i < beadModel.beadContour.size(); i++) {
        const Point2d &current = beadModel.beadContour[i - 1];
        const Point2d &next = beadModel.beadContour[i];

        double halfRowDist = abs(current.x - next.x) / 2;
        double halfColDist = abs(current.y - next.y) / 2;
        double halfDist = getDistance(current, next) / 2;
        double angle = getAngle(current, next);

        Point2d offsetUpper = getPerpOffset(current, next, -halfWidth);
        Point2d offsetLower = getPerpOffset(current, next, halfWidth);

        double colShift = halfDist * sin(angle);
        double rowShift = halfDist * cos(angle);

        lowerContour.emplace_back(int(offsetLower.y - colShift), int(offsetLower.x - rowShift));
        upperContour.emplace_back(int(offsetUpper.y - colShift), int(offsetUpper.x - rowShift));

        if (i == beadModel.beadContour.size() - 1) {
            angle = getAngle(next, current);

			colShift = halfDist * sin(angle);
			rowShift = halfDist * cos(angle);

			lowerContour.emplace_back(int(offsetLower.y - colShift), int(offsetLower.x - rowShift));
			upperContour.emplace_back(int(offsetUpper.y - colShift), int(offsetUpper.x - rowShift));
        }
    }

    Contour &resultContour = lowerContour;
    resultContour.insert(resultContour.end(), upperContour.rbegin(), upperContour.rend());

    return resultContour;
}


void drawBeadContour(Mat &img, const Contour &contour) {
    for (size_t i = 1; i < contour.size(); i++) {
        const Point2i& current = contour[i - 1];
        const Point2i& next = contour[i];

        line(img, reverse(current), reverse(next), COLOR_BLUE, 2);
        circle(img, reverse(current), 3, COLOR_GREEN, -1);
		circle(img, reverse(next), 3, COLOR_GREEN, -1);

	}
}

void drawBeadModel(Mat &img, const BeadModel &model) {
    const Contour &contour = model.beadContour;

    if (contour.size() < 2)
        return;

    drawBeadContour(img, contour);
    const Contour surroundingContour = getSurroundingContour(model, model.positionTol);

    for (size_t i = 1; i < surroundingContour.size(); i++) {
        const Point2i& current = surroundingContour[i - 1];
        const Point2i& next = surroundingContour[i];

        line(img, current, next, COLOR_RED, 2);
    }
}