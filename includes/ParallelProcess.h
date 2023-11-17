//
// Created by jtag on 11/17/23.
//

#ifndef MASS_IMAGE_PROCESSING_PARALLELPROCESS_H
#define MASS_IMAGE_PROCESSING_PARALLELPROCESS_H

#include <future>
#include <queue>
#include <filesystem>
#include "includes/Image.h"

namespace fs = std::filesystem;

class ParallelProcess {
public:
    ParallelProcess(fs::path input, fs::path output);

    int run(const cv::Vec3b &find, const cv::Vec3b &replace);

private:
    void loadImages();

    void performColorManipulation(const cv::Vec3b &find, const cv::Vec3b &replace);

    void saveImages();

private:
    const fs::path _input;
    const fs::path _output;
    std::queue<std::future<void>> _changeColorFutures;
    std::queue<std::future<void>> _loadFutures;
    std::queue<std::future<void>> _saveFutures;
    std::queue<std::unique_ptr<Image>> _imagesLoad;
    std::vector<std::unique_ptr<Image>> _images;
};


#endif //MASS_IMAGE_PROCESSING_PARALLELPROCESS_H
