/**
 * @file drawingDefs.hpp
 * @brief Macro definitions to assist with organizing drawing
 */

#ifndef DRAW_MACROS_HPP
#define DRAW_MACROS_HPP

#include <opencv2/opencv.hpp>

// Color macros
#define COLOR_BLUE CV_RGB(0, 0, 255)
#define COLOR_GREEN CV_RGB(0, 255, 0)
#define COLOR_RED CV_RGB(255, 0, 0)
#define COLOR_BLACK CV_RGB(0, 0, 0)
#define COLOR_DARKVIOLET CV_RGB(148, 0, 211)
#define COLOR_ORANGE CV_RGB(255, 165, 0)
#define COLOR_CYAN CV_RGB(0, 255, 255)
#define COLOR_WHITE CV_RGB(255, 255, 255)

// Reverse a point to convert from (row, col) to (col, row) to use for OpenCV drawing functions
cv::Point2d reverse(const cv::Point2d &pt);

#endif
