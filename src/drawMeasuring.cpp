#include "drawMeasuring.hpp"

constexpr int RADIUS = 2;
constexpr int CIRCLE_THICKNESS = -1;

using namespace cv;

void drawMeasurePos(Mat &img, const MeasurePosResults &results, const Scalar &color) {
    std::vector<Point2d> posEdges = results.edgePositions;

    auto posIter = posEdges.begin();

    while (posIter < posEdges.end()) {
        circle(img, reverse(*posIter), RADIUS, color, CIRCLE_THICKNESS, LINE_AA);

        std::advance(posIter, 1);
    }
}

void drawMeasurePairs(Mat &img, const MeasurePairsResults &results, const Scalar &colorLeft, const Scalar &colorRight) {
    std::vector<Point2d> posFirst = results.posFirst;
    std::vector<Point2d> posSecond = results.posSecond;

    auto p1 = posFirst.begin();
    auto p2 = posSecond.begin();

    while (p1 < posFirst.end() && p2 < posSecond.end()) {
        circle(img, reverse(*p1), RADIUS, colorLeft, CIRCLE_THICKNESS, LINE_AA);
        circle(img, reverse(*p2), RADIUS, colorRight, CIRCLE_THICKNESS, LINE_AA);

        std::advance(p1, 1);
        std::advance(p2, 1);
    }
}
