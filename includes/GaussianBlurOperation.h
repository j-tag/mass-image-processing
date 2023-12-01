//
// Created by jtag on 12/1/23.
//

#ifndef MASS_IMAGE_PROCESSING_GAUSSIANBLUROPERATION_H
#define MASS_IMAGE_PROCESSING_GAUSSIANBLUROPERATION_H


#include <opencv2/core/types.hpp>
#include "ImageOperation.h"

/**
 * Used to encapsulate details about a gaussian blur operation on images.
 */
class GaussianBlurOperation : public ImageOperation {
public:

    /**
     * Constructs data about a gaussian blur operation.
     * @param size
     */
    explicit GaussianBlurOperation(const cv::Size &size)
            : ImageOperation(Operation::GaussianBlur), _size(size) {}

    /**
     * Returns the size of blur that should be applied on images.
     * @return Blur size.
     */
    [[nodiscard]] cv::Size getSize() const {
        return _size;
    }

private:
    /**
     * Holds the blur size.
     */
    const cv::Size _size;
};


#endif //MASS_IMAGE_PROCESSING_GAUSSIANBLUROPERATION_H
