//
// Created by jtag on 12/1/23.
//

#ifndef MASS_IMAGE_PROCESSING_COLORCHANGEOPERATION_H
#define MASS_IMAGE_PROCESSING_COLORCHANGEOPERATION_H


#include <opencv2/core/matx.hpp>
#include "ImageOperation.h"

/**
 * Used to encapsulate details about a color change operation on images.
 */
class ColorChangeOperation : public ImageOperation {
public:
    /**
     * Constructs data about a color manipulation operation.
     * @param find
     * @param replace
     */
    ColorChangeOperation(const cv::Vec3b &find, const cv::Vec3b &replace)
            : ImageOperation(Operation::ColorChange), _find(find), _replace(replace) {}

    /**
     * Returns the color that should be found to be replaced later.
     * @return Color to be found.
     */
    [[nodiscard]] cv::Vec3b getFind() const {
        return _find;
    }

    /**
     * Returns the color that should be replaced with founded color.
     * @return Color to be replaced.
     */
    [[nodiscard]] cv::Vec3b getReplace() const {
        return _replace;
    }

private:
    /**
     * Holds the color that should be found to be replaced later.
     */
    const cv::Vec3b _find;

    /**
     * Holds the color that should be replaced with founded color.
     */
    const cv::Vec3b _replace;
};


#endif //MASS_IMAGE_PROCESSING_COLORCHANGEOPERATION_H
