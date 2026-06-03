/**
 * @file drawFuzzy.hpp
 * @brief Drawing functions for fuzzy 1D measuring
 */

#ifndef DRAW_FUZZY_HPP
#define DRAW_FUZZY_HPP

#include "FuzzyStructs.hpp"
#include "drawingDefs.hpp"

/**
 * @fn void drawFuzzyPos(cv::Mat &img, const FuzzyMeasurePosResult &results, const cv::Scalar color = COLOR_RED)
 * @brief Draws the edges detected from running fuzzyMeasurePos onto the image provided
 * 
 * @param img Color input image.
 * @param results A FuzzyMeasurePosResult struct
 * @param color Color to draw the edges in. Default value is Red
 */
void drawFuzzyPos(cv::Mat &img, const FuzzyMeasurePosResult &results, const cv::Scalar &color = COLOR_RED);

/**
 * @fn drawFuzzyPairs(cv::Mat &img, const FuzzyMeasurePairsResult &results, const bool drawCenter = false,
                      const cv::Scalar colorLeft = COLOR_ORANGE, const cv::Scalar colorRight = COLOR_DARKVIOLET, const cv::Scalar colorCenter = COLOR_RED)
 * @brief Draws the edges detected from running fuzzyMeasurePairs onto the image provided
 * 
 * @param img Color input image.
 * @param results A FuzzyMeasurePairsResult struct
 * @param drawCenter Boolean toggle whether to draw the center of the edge points or not.
 * @param colorLeft The color to draw the left edges in. Default value is Orange
 * @param colorRight The color to draw the right edges in. Default value is DarkViolet
 * @param colorCenter The color to draw the center of the edges in. Default value is Red
 */
void drawFuzzyPairs(cv::Mat &img, const FuzzyMeasurePairsResult &results, bool drawCenter = false,
                    const cv::Scalar &colorLeft = COLOR_ORANGE, const cv::Scalar &colorRight = COLOR_DARKVIOLET,
                    const cv::Scalar &colorCenter = COLOR_RED);

#endif  // !DRAW_FUZZY
