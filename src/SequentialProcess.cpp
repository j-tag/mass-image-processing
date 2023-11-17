//
// Created by jtag on 11/17/23.
//

#include <utility>
#include <iostream>
#include <opencv4/opencv2/imgcodecs.hpp>
#include "includes/SequentialProcess.h"
#include "includes/BufferedIO.h"


SequentialProcess::SequentialProcess(fs::path input, fs::path output) : _input(std::move(input)),
                                                                        _output(std::move(output)) {}

int SequentialProcess::run(const Vec3b &find, const Vec3b &replace, bool buffered) {

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
        // Perform color manipulation
        const unsigned int tolerance = 30;
        std::transform(img.begin<Vec3b>(), img.end<Vec3b>(), img.begin<Vec3b>(), [&](auto &pixel) {
            if (norm(pixel, find, NORM_L2SQR) < tolerance * tolerance) {
                return replace;
            } else {
                return pixel;
            }
        });

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
