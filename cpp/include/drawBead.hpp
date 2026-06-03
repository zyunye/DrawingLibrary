/**
 * @file drawBead.hpp
 * @brief Drawing functions for bead inspection
 */

#ifndef DRAW_BEAD_HPP
#define DRAW_BEAD_HPP

#include "beadModel.hpp"
#include "drawingDefs.hpp"

void drawBeadContour(cv::Mat &img, const Contour &contour);
void drawBeadModel(cv::Mat &img, const BeadModel &model);

#endif