/**
 * @file drawMeasuring.hpp
 * @brief Drawing functions for non-fuzzy 1D measuring
 */

#ifndef DRAW_MEASURING_HPP
#define DRAW_MEASURING_HPP

#include "MeasuringResults.hpp"
#include "drawingDefs.hpp"

/**
 * @fn drawMeasurePos(cv::Mat &img, const MeasurePosResult &results, const cv::Scalar color = COLOR_RED)
 * @brief Draws the edges detected from running measurePos onto the image provided
 * 
 * @param img Color input image.
 * @param results A MeasurePosResult struct
 * @param color The color to draw the edge results in. Default value is Red
 */
void drawMeasurePos(cv::Mat &img, const MeasurePosResults &results, const cv::Scalar &color = COLOR_RED);

/**
 * @fn (cv::Mat &img, const MeasurePairsResult &results,
                      const cv::Scalar colorLeft = COLOR_ORANGE, const cv::Scalar colorRight = COLOR_DARKVIOLET)
 * @brief Draws the edges detected from running measurePairs onto the image provided
 * 
 * @param img Color input image.
 * @param results A MeasurePairsResult struct
 * @param colorLeft The color to draw the left edge in. Default value is Orange
 * @param colorRight The color to draw the right edge in. Default value is DarkViolet
 */
void drawMeasurePairs(cv::Mat &img, const MeasurePairsResults &results,
                      const cv::Scalar &colorLeft = COLOR_ORANGE, const cv::Scalar &colorRight = COLOR_DARKVIOLET);

#endif  //  DRAW_MEASURING.hpp
