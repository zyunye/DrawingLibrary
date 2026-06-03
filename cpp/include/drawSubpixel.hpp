/**
 * @file drawSubpixel.hpp
 * @brief Subpixel drawing functions 
 */

#ifndef DRAW_SUBPIXEL_HPP
#define DRAW_SUBPIXEL_HPP

#include "drawingDefs.hpp"

/**
 * @brief Class to assist with condensing all of the subpixel drawing into one place and to make it easy to work with.
 */
class SubpixelWorkspace {
protected:
    int zoomScale;
    cv::Mat zoomedImage;
    cv::Mat temporaryImg;
    bool retTemp;

    // Top boundary (row value) of the section of the original image that was cropped out.
    int leftRow;
    // Left boundary (column value) of the section of the original image that was cropped out.
    int leftColumn;
    // Half length of a side of the square region.
    int buffer;

public:
    /**
     * @brief Constructs a SubpixelWorkspace to perform subpixel drawing in a specific region of an image.
     * @details Crops out a square region of the image given based on the parameters given and creates a new zoomed image
     * with which all the drawing functions operate on.
     * 
     * @param img Original image to be cropped.
     * @param row Center row position of the square region to be cropped out.
     * @param col Center column position of the square region to be cropped.
     * @param scale How much to zoom into the cropped section.
     * @param buffer How many pixels (in each direction) from the center of the square to include.
     */
    SubpixelWorkspace(const cv::Mat &img, double row, double col, int scale, int buffer);

    /**
     * @brief Draws a circle on the zoomed image
     * @details Automatically transforms circle parameters from the original coordinate space to the zoomed coordinate space
     * and draws it on the zoomed image
     * 
     * @param row Row coordinate of the center of the circle in the ORIGINAL coordinate space.
     * @param col Column coordinate of the center of the circle in the ORIGINAL coordinate space.
     * @param radius ORIGINAL radius of the circle.
     * @param color Color to draw the circle in.
     */
    void drawCircle(double row, double col, double radius, const cv::Scalar &color = COLOR_GREEN);

    void drawTempCircle(double row, double col, double radius, const cv::Scalar &color = COLOR_GREEN);

    /**
     * @brief Draws a point on the zoomed image
     * @details Automatically transforms circle parameters from the original coordinate space to the zoomed coordinate space
     * and draws it on the zoomed image
     * 
     * @param row Row coordinate of the center of the circle in the ORIGINAL coordinate space.
     * @param col Column coordinate of the center of the circle in the ORIGINAL coordinate space.
     * @param color Color to draw the circle in.
     */
    void drawPoint(double row, double col, const cv::Scalar &color = COLOR_GREEN);

    void drawTempPoint(double row, double col, const cv::Scalar &color = COLOR_GREEN);

    /**
     * @brief Draws a line on the zoomed image
     * @details Automatically transforms line parameters from the original coordinate space to the zoomed coordinate space
     * and draws it on the zoomed image
     * 
     * @param rowStart Starting row coordinate of the line in the ORIGINAL coordinate space.
     * @param colStart Starting column coordinate of the line in the ORIGINAL coordinate space.
     * @param rowEnd Ending row coordinate of the line in the ORIGINAL coordinate space.
     * @param colEnd Ending column coordinate of the line in the ORIGINAL coordinate space.
     * @param color Color to draw the line in.
     */
    void drawLine(double rowStart, double colStart, double rowEnd, double colEnd, const cv::Scalar &color = COLOR_GREEN);

    void drawTempLine(double rowStart, double colStart, double rowEnd, double colEnd, const cv::Scalar &color = COLOR_GREEN);

    /**
     * @brief Draws a rectangle on the zoomed image
     * @details Automatically transforms rectangle parameters from the original coordinate space to the zoomed coordinate space
     * and draws it on the zoomed image
     * 
     * @param corners Vector of OpenCV points which specify the corners of the rectangle in the ORIGINAL coordinate space.
     * @param color Color to draw the rectangle in.
     * @param drawCorners Boolean toggle to circle the corners of the rectangle in the zoomed image.
     */
    void drawRect(const std::vector<cv::Point2d> &corners, const cv::Scalar &color = COLOR_GREEN, bool drawCorners = false);

    void drawTempRect(const std::vector<cv::Point2d> &corners, const cv::Scalar &color = COLOR_GREEN, bool drawCorners = false);

    /**
     * @brief Draws an ellipse on the zoomed image
     * @details Automatically transforms ellipse parameters from the original coordinate space to the zoomed coordinate space
     * and draws it on the zoomed image
     * 
     * @param row Row coordinate of the center of the ellipse in the ORIGINAL coordinate space.
     * @param col Column coordinate of the center of the ellipse in the ORIGINAL coordinate space.
     * @param phi Mathematically positive rotation angle of the ellipse. Assumes radians are given.
     * @param shortRadius Length of the short radius in the ORIGINAL coordinate space.
     * @param longRadius Length of the long radius in the ORIGINAL coordinate space.
     * @param color Color to draw the ellipse in.
     */
    void drawEllipse(double row, double col, double phi, double shortRadius, double longRadius, const cv::Scalar &color = COLOR_GREEN);

    void drawTempEllipse(double row, double col, double phi, double shortRadius, double longRadius, const cv::Scalar &color = COLOR_GREEN);

    /**
     * @brief Returns the zoomed image with all the requested drawings.
     * 
     * @return A reference to the zoomed-in image with drawings.
     */
    const cv::Mat &getZoomedImage() {
        if (retTemp) {
            retTemp = false;
            return temporaryImg;
        }
        return zoomedImage;
    };
};

cv::Point2d reverse(const cv::Point2d &pt) {
    return {pt.y, pt.x};
}

#endif
