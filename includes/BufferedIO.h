//
// Created by jtag on 11/17/23.
//

#ifndef MASS_IMAGE_PROCESSING_BUFFEREDIO_H
#define MASS_IMAGE_PROCESSING_BUFFEREDIO_H

#include <opencv2/core.hpp>
#include <filesystem>

namespace fs = std::filesystem;
using namespace cv;

/**
 * Use this class to read and write data using buffers.
 */
class BufferedIO {
public:
    /**
     * Reads the file and returns its data back as a buffer.
     * Could be useful for reading images.
     * @param path The image file to be read
     * @return OpenCV image mat
     */
    static std::vector<uint8_t> read(const fs::path &path);

    /**
     * Writes an OpenCV mat to path with buffer.
     * @param path
     * @param img
     */
    static void write(const fs::path &path, const Mat &img);
};


#endif //MASS_IMAGE_PROCESSING_BUFFEREDIO_H
