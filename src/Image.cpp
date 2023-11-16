//
// Created by jtag on 11/16/23.
//

#include "includes/Image.h"
#include <iostream>
#include <utility>

Image::Image(Mat img) : _img(std::move(img)) {

}

void Image::changeColor(const Vec3b find, const Vec3b replace) {
    const unsigned int tolerance = 30;

    std::transform(_img.begin<Vec3b>(), _img.end<Vec3b>(), _img.begin<Vec3b>(), [&](auto &pixel) {
        if (norm(pixel, find, NORM_L2SQR) < tolerance * tolerance) {
            return replace;
        } else {
            return pixel;
        }
    });
}

void Image::save(const String &filename) {
    if (!imwrite(filename, _img)) {
        std::cerr << "Error writing image: " << filename << '\n';
    }
}
