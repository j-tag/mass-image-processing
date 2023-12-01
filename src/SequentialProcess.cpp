//
// Created by jtag on 11/17/23.
//

#include <utility>
#include <iostream>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include "includes/SequentialProcess.h"
#include "includes/BufferedIO.h"
#include "includes/ColorChangeOperation.h"
#include "includes/GaussianBlurOperation.h"


SequentialProcess::SequentialProcess(fs::path input, fs::path output) : _input(std::move(input)),
                                                                        _output(std::move(output)) {}

int SequentialProcess::run(const std::vector<std::reference_wrapper<ImageOperation>> &operations, bool buffered) {

    for (const auto &entry: fs::directory_iterator(_input)) {

        std::cout << "Loading: " << entry.path() << std::endl;
        // Load image
        auto load = [&buffered](auto &&path) -> Mat {
            if (buffered) {
                const auto data = BufferedIO::read(path);
                return imdecode(
                        data,
                        IMREAD_COLOR
                );
            }
            return imread(path);
        };
        auto img = load(entry.path());

        std::cout << "Processing: " << entry.path() << std::endl;

        // Go through each operation and apply it sequentially
        for (const auto &operation: operations) {

            switch (operation.get().getOperation()) {
                case ImageOperation::Operation::ColorChange: {
                    // Color change operation
                    const auto colorChangeOperation = (ColorChangeOperation &&) operation.get();
                    SequentialProcess::colorChange(img, colorChangeOperation);
                    break;
                }
                case ImageOperation::Operation::GaussianBlur:
                    // Gaussian blur operation
                    const auto gaussianBlurOperation = (GaussianBlurOperation &&) operation.get();
                    cv::GaussianBlur(img, img, gaussianBlurOperation.getSize(), 0);
                    break;
            }
        }
        std::cout << "Saving: " << entry.path() << std::endl;
        // Save image
        std::filesystem::path outputPath = _output / entry.path().filename();
        if (buffered) {
            BufferedIO::write(outputPath, img);
        } else {
            if (!imwrite(outputPath, img)) {
                std::cerr << "Error writing image: " << outputPath << std::endl;
            }
        }

    }
    return EXIT_SUCCESS;
}

void SequentialProcess::colorChange(cv::Mat &img, const ColorChangeOperation &operation) {
    // Perform color manipulation
    const unsigned int tolerance = 30;
    const auto find = operation.getFind();
    const auto replace = operation.getReplace();
    std::transform(img.begin<Vec3b>(), img.end<Vec3b>(), img.begin<Vec3b>(),
                   [&](auto &pixel) {
                       if (norm(pixel, find, NORM_L2SQR) < tolerance * tolerance) {
                           return replace;
                       } else {
                           return pixel;
                       }
                   });
}
