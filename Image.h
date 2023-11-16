//
// Created by jtag on 11/16/23.
//

#ifndef MASS_IMAGE_PROCESSING_IMAGE_H
#define MASS_IMAGE_PROCESSING_IMAGE_H

#include <opencv4/opencv2/imgcodecs.hpp>

using namespace cv;

class Image {
public:
    explicit Image(Mat img);

    void changeColor(Vec3b find, Vec3b replace);

    void save(const String &filename);

private:
    Mat _img;
};


#endif //MASS_IMAGE_PROCESSING_IMAGE_H
