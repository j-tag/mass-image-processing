//
// Created by jtag on 11/17/23.
//

#include <fstream>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include "includes/BufferedIO.h"

std::vector<uint8_t> BufferedIO::read(const fs::path &path) {
    std::ifstream inputStream(path, std::ios::binary);
    std::vector<uint8_t> data = std::vector<uint8_t>(std::istreambuf_iterator<char>(inputStream),
                                                     std::istreambuf_iterator<char>());
    return data;
}

void BufferedIO::write(const fs::path &path, const Mat &img) {
    std::ofstream outputStream(path, std::ios::binary);
    std::vector<uchar> buffer;
    cv::imencode(".jpg", img, buffer);
    outputStream.write(reinterpret_cast<const char *>(buffer.data()), static_cast<std::streamsize>(buffer.size()));
}
