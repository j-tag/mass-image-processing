//
// Created by jtag on 11/16/23.
//

#ifndef MASS_IMAGE_PROCESSING_IMAGE_H
#define MASS_IMAGE_PROCESSING_IMAGE_H

#include <opencv2/imgcodecs.hpp>
#include <filesystem>

using namespace cv;
namespace fs = std::filesystem;

class Image {
public:
    explicit Image(fs::path path);

    void load();

    void loadBuffered();

    void changeColor(Vec3b find, Vec3b replace);

    void save(const String &filename);

    void saveBuffered(const String &filename);

    [[nodiscard]] fs::path getPath() const;

private:
    Mat _img;
    const fs::path _path;
};


#endif //MASS_IMAGE_PROCESSING_IMAGE_H
