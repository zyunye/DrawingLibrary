/**
 * @file drawHandles.hpp
 * @brief Functions for drawing MeasureHandles
 */

#ifndef DRAW_MEASURE_HANDLES_HPP
#define DRAW_MEASURE_HANDLES_HPP

#include "ArcElement.hpp"
#include "RectElement.hpp"
#include "ArcTransposedElement.hpp"
#include "drawSubpixel.hpp"

class SubpixelMeasureWorkspace : public SubpixelWorkspace {
    using SubpixelWorkspace::SubpixelWorkspace;
public:
    /**
     * @brief Draws a MeasureRectangle on the zoomed image
     * @details Wrapper method which accepts a MeasureRectangle and internally calls the drawRect method.
     *
     * @param measure MeasureRectangle from the ORIGINAL coordinate space to draw on the zoomed image.
     * @param color Color to draw the MeasureRectangle in.
     * @param drawCorners Boolean toggle to circle the corners of the rectangle in the zoomed image.
     */
    void drawMeasureHandle(RectangleElement &measure, const cv::Scalar &color = COLOR_GREEN, bool drawCorners = false);

    /**
     * @brief Draws a MeasureArc on the zoomed image
     * @details Wrapper method which accepts a MeasureArc and internally calls the drawCircle method.
     *
     * @param measure MeasureArc from the ORIGINAL coordinate space to draw on the zoomed image.
     * @param color Color to draw the MeasureArc in.
     */
    void drawMeasureHandle(ArcElement &measure, const cv::Scalar &color = COLOR_GREEN);

    /**
 * @brief Draws a MeasureArc on the zoomed image
 * @details Wrapper method which accepts a MeasureArc and internally calls the drawCircle method.
 *
 * @param measure MeasureArc from the ORIGINAL coordinate space to draw on the zoomed image.
 * @param color Color to draw the MeasureArc in.
 */
    void drawMeasureHandle(ArcTransposedElement &measure, const cv::Scalar &color = COLOR_GREEN);
};

/**
 * @fn drawMeasureHandle(cv::Mat &img, const MeasureRectangle &measureHandle, bool drawCorners = false, const cv::Scalar &color = COLOR_GREEN)
 * @brief Draws the MeasureRectangle onto the image provided
 * 
 * @param img Color input image.
 * @param measureHandle The MeasureHandle object.
 * @param color The color to draw the MeasureHandle in. Default value is green (b=0, g=255, r=0).
 * @param drawCorners Boolean toggle whether the corners of the MeasureRectangle should be circled.
 */
void drawMeasureHandle(cv::Mat &img, const RectangleElement &measureHandle, const cv::Scalar &color = COLOR_GREEN,
                       bool drawCorners = false);

/**
 * @fn drawMeasuringHandle(const cv::Mat &img, const MeasureArc &MeasureHandle)
 * @brief Draws the MeasureArc onto the image provided
 * 
 * @param img Color input image.
 * @param measureHandle The MeasureHandle object.
 * @param color The color to draw the MeasureHandle in. Default value is green (b=0, g=255, r=0).
 */
void drawMeasureHandle(cv::Mat &img, const ArcElement &measureHandle, const cv::Scalar &color = COLOR_GREEN);

/**
 * @fn drawMeasuringHandle(const cv::Mat &img, const MeasureArc &MeasureHandle)
 * @brief Draws the MeasureArc onto the image provided
 *
 * @param img Color input image.
 * @param measureHandle The MeasureHandle object.
 * @param color The color to draw the MeasureHandle in. Default value is green (b=0, g=255, r=0).
 */
void drawMeasureHandle(cv::Mat &img, const ArcTransposedElement &measureHandle, const cv::Scalar &color = COLOR_GREEN);

#endif