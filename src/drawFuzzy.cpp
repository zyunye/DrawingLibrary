#include "drawFuzzy.hpp"

constexpr int RADIUS = 2;
constexpr int CIRCLE_THICKNESS = -1;

using namespace cv;

/** 
 * As a technicality this implementation is literally exactly the same as the non fuzzy variant.
 * For nomenclature consistency with pairs drawing (which IS different between fuzzy and non fuzzy)
 * I've decided to actually implement this instead of delegating to a templated method, 
 * which would make the drawMeasuring source sort of confusing and a bit inconsistent when only one of its methods is templated and not the other.
 */
void drawFuzzyPos(Mat &img, const FuzzyMeasurePosResult &results, const Scalar &color) {
    std::vector<Point2d> posEdges = results.edgePositions;

    auto posIter = posEdges.begin();

    while (posIter < posEdges.end()) {
        circle(img, reverse(*posIter), RADIUS, color, CIRCLE_THICKNESS, LINE_AA);

        std::advance(posIter, 1);
    }
}

void drawFuzzyPairs(Mat &img, const FuzzyMeasurePairsResult &results, bool drawCenter, const Scalar &colorLeft,
                    const Scalar &colorRight, const Scalar &colorCenter) {
    std::vector<Point2d> posFirst = results.posFirst;
    std::vector<Point2d> posSecond = results.posSecond;

    auto p1 = posFirst.begin();
    auto p2 = posSecond.begin();

    while (p1 < posFirst.end() && p2 < posSecond.end()) {
        circle(img, *p1, RADIUS, colorLeft, CIRCLE_THICKNESS, LINE_AA);
        circle(img, *p2, RADIUS, colorRight, CIRCLE_THICKNESS, LINE_AA);
        std::advance(p1, 1);
        std::advance(p2, 1);
    }

    if (drawCenter) {
        std::vector<Point2d> posCenter = results.posCenter;
        auto pc = posCenter.begin();

        while (pc < posCenter.end()) {
            circle(img, *pc, RADIUS, colorCenter, CIRCLE_THICKNESS, LINE_AA);

            std::advance(pc, 1);
        }
    }
}
