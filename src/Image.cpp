//
// Created by jtag on 11/16/23.
//

#include "includes/Image.h"
#include "includes/BufferedIO.h"
#include "includes/ColorChangeOperation.h"
#include "includes/GaussianBlurOperation.h"
#include <iostream>
#include <utility>
#include <execution>
#include <opencv2/imgproc.hpp>

Image::Image(fs::path path) : _path(std::move(path)) {}

void Image::changeColor(const Vec3b &find, const Vec3b &replace) {
    const unsigned int tolerance = 30;

    // If you look carefully, here we have `std::execution::par` for the `exec` parameter, which causes this
    // transformation to use TBB and run the operation in parallel
    std::transform(std::execution::par, _img.begin<Vec3b>(), _img.end<Vec3b>(), _img.begin<Vec3b>(),
                   [&](auto &pixel) {
                       if (norm(pixel, find, NORM_L2SQR) < tolerance * tolerance) {
                           return replace;
                       } else {
                           return pixel;
                       }
                   });
}

void Image::gaussianBlur(const Size &size) {
    // Apply Gaussian blur
    // Process each row of image in parallel and concurrently
    tbb::parallel_for(tbb::blocked_range<int>(0, _img.rows),
                      [&](tbb::blocked_range<int> r) {
                          for (int i = r.begin(); i < r.end(); ++i) {
                              cv::GaussianBlur(_img.row(i), _img.row(i), size, 0);
                          }
                      });
}

void Image::save(const String &filename) {
    if (!imwrite(filename, _img)) {
        std::cerr << "Error writing image: " << filename << std::endl;
    }
}

void Image::saveBuffered(const String &filename) {
    BufferedIO::write(filename, _img);
}

void Image::load() {
    _img = imread(_path);
}

void Image::loadBuffered() {
    const auto data = BufferedIO::read(_path);
    cv::imdecode(
            data,
            cv::IMREAD_COLOR,
            &_img
    );
}

void Image::orderedOperations(const std::vector<std::reference_wrapper<ImageOperation>> &operations) {
    // Go through each operation and preserve their order and run them one-by-one. This is important in
    // situations where we can't apply multiple manipulations in parallel, because the order of manipulations
    // will not be reserved for different parts of image if we run operations in parallel, so we end up with artifacts
    // on images which caused by not preserving the order of operations e.g. one part of image is blurred first and
    // then replaced a color which is not correct and should be the opposite direction.
    for (const auto &operation: operations) {
        switch (operation.get().getOperation()) {
            case ImageOperation::Operation::ColorChange: {
                // Color change operation
                const auto colorChangeOperation = (ColorChangeOperation &&) operation.get();
                this->changeColor(colorChangeOperation.getFind(), colorChangeOperation.getReplace());
                break;
            }
            case ImageOperation::Operation::GaussianBlur:
                // Gaussian blur operation
                const auto gaussianBlurOperation = (GaussianBlurOperation &&) operation.get();
                this->gaussianBlur(gaussianBlurOperation.getSize());
                break;
        }
    }
}

fs::path Image::getPath() const {
    return _path;
}
