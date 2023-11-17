//
// Created by jtag on 11/17/23.
//

#ifndef MASS_IMAGE_PROCESSING_BUFFEREDIO_H
#define MASS_IMAGE_PROCESSING_BUFFEREDIO_H

#include <opencv2/core.hpp>
#include <filesystem>

namespace fs = std::filesystem;
using namespace cv;

class BufferedIO {
public:
    static std::vector<uint8_t> read(const fs::path &path);

    static void write(const fs::path &path, const Mat &img);
};


#endif //MASS_IMAGE_PROCESSING_BUFFEREDIO_H
