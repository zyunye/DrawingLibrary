/**
 * @file drawMetrology.hpp
 * @brief Drawing functions for MetrologyObjects
 */

#ifndef DRAW_METROLOGY_HPP
#define DRAW_METROLOGY_HPP

#include "metrologyObject.hpp"
#include "drawHandles.hpp"

class SubpixelMetrologyWorkspace : public SubpixelMeasureWorkspace {
    using SubpixelMeasureWorkspace::SubpixelMeasureWorkspace;
public:

    /**
     * @brief Draws an ArcObject on the zoomed image
     * @details Wrapper method which accepts a ArcObject and internally calls the drawCircle method.
     * Does NOT draw the MeasureHandles which encompass the ArcObject.
     *
     * @param obj ArcObject from the ORIGINAL coordinate space to draw on the zoomed image.
     * @param color Color to draw the ArcObject in.
     */
    void drawMetrology(ArcObject &obj, const cv::Scalar &color = COLOR_GREEN);

    /**
     * @brief Draws an EllipseObject on the zoomed image
     * @details Wrapper method which accepts a EllipseObject and internally calls the drawEllipse method.
     * Does NOT draw the MeasureHandles which encompass the EllipseObject.
     *
     * @param obj EllipseObject from the ORIGINAL coordinate space to draw on the zoomed image.
     * @param color Color to draw the EllipseObject in.
     */
    void drawMetrology(EllipseObject &obj, const cv::Scalar &color = COLOR_GREEN);

    /**
     * @brief Draws a LineObject on the zoomed image
     * @details Wrapper method which accepts a LineObject and internally calls the drawLine method.
     * Does NOT draw the MeasureHandles which encompass the LineObject.
     *
     * @param obj LineObject from the ORIGINAL coordinate space to draw on the zoomed image.
     * @param color Color to draw the LineObject in.
     */
    void drawMetrology(LineObject &obj, const cv::Scalar &color = COLOR_GREEN);

    /**
     * @brief Draws a RectObject on the zoomed image
     * @details Wrapper method which accepts a RectObject and internally calls the drawRect method.
     * Does NOT draw the MeasureHandles which encompass the RectObject.
     *
     * @param obj RectObject from the ORIGINAL coordinate space to draw on the zoomed image.
     * @param color Color to draw the RectObject in.
     * @param drawCorners Boolean toggle to circle the corners of the rectangle in the zoomed image.
     */
    void drawMetrology(RectObject &obj, const cv::Scalar &color = COLOR_GREEN, bool drawCorners = false);

};

/**
 * @fn drawArcObject(cv::Mat &img, const ArcObject &obj, const cv::Scalar &color = COLOR_GREEN)
 * @brief Draw an ArcObject onto an image.
 * 
 * @param img Color input image.
 * @param obj ArcObject to be drawn.
 * @param color Color of the arc.
 */
void drawArcObject(cv::Mat &img, const ArcObject &obj, const cv::Scalar &color = COLOR_GREEN);

/**
 * @fn drawEllipseObject(cv::Mat &img, const EllipseObject &obj, const cv::Scalar &color = COLOR_GREEN)
 * @brief Draw an EllipseObject onto an image.
 * 
 * @param img Color input image.
 * @param obj Ellipse to be drawn.
 * @param color Color of the elliptical arc
 */
void drawEllipseObject(cv::Mat &img, const EllipseObject &obj, const cv::Scalar &color = COLOR_GREEN);

/**
 * @fn drawRectObject(cv::Mat &img, const RectObject &obj, const cv::Scalar &color = COLOR_GREEN)
 * @brief Draw a RectObject onto an image.
 * 
 * @param img Color input image.
 * @param obj RectObject to be drawn.
 * @param color Color of the rectangle.
 */
void drawRectObject(cv::Mat &img, const RectObject &obj, const cv::Scalar &color = COLOR_GREEN, const bool drawCorners = false);

/**
 * @fn drawLineObject(cv::Mat &img, const LineObject &obj, const cv::Scalar &color = COLOR_GREEN)
 * @brief Draw a LineObject onto an image.
 * 
 * @param img Color input image.
 * @param obj LineObject to be drawn.
 * @param color Color of the line.
 * @param drawEndPoints Toggle whether to draw the starting point and ending point of the line.
 */
void drawLineObject(cv::Mat &img, const LineObject &obj, const cv::Scalar &color = COLOR_GREEN, const bool drawEndPoints = false);

#endif  //  DRAW_METROLOGY.hpp