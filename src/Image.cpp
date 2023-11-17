//
// Created by jtag on 11/16/23.
//

#include "includes/Image.h"
#include "includes/BufferedIO.h"
#include <iostream>
#include <utility>
#include <execution>

Image::Image(fs::path path) : _path(std::move(path)) {}

void Image::changeColor(const Vec3b find, const Vec3b replace) {
    const unsigned int tolerance = 30;

    std::transform(std::execution::par, _img.begin<Vec3b>(), _img.end<Vec3b>(), _img.begin<Vec3b>(),
                   [&](auto &pixel) {
        if (norm(pixel, find, NORM_L2SQR) < tolerance * tolerance) {
            return replace;
        } else {
            return pixel;
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

fs::path Image::getPath() const {
    return _path;
}
