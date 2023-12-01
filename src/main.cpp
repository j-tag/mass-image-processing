#include <iostream>
#include <opencv2/core.hpp>
#include "includes/ParallelProcess.h"
#include "includes/SequentialProcess.h"
#include "includes/ColorChangeOperation.h"
#include "includes/GaussianBlurOperation.h"


int main(int argc, char const **argv) {

    if (argc < 3 || argc > 5) {
        std::cerr << "Usage: mass_image_processing <input_dir> <output_dir> [-p,-s] [-nb,-b]\n"
                     "-p: parallel processing (default)\n"
                     "-s: sequential processing\n"
                     "-nb: non-buffered I/O (default)\n"
                     "-b: buffered I/O\n";
        return EXIT_FAILURE;
    }

    ParallelProcess par(argv[1], argv[2]);
    SequentialProcess seq(argv[1], argv[2]);

    // Color manipulation values (replace a certain color in images)
    // Note: colors are BGR formatted in OpenCV
    const cv::Vec3b from1 = {190, 190, 190};
    const cv::Vec3b to1 = {85, 85, 255};
    ColorChangeOperation colorChangeOperation1(from1, to1);
    // Second color manipulation
    const cv::Vec3b from2 = {162, 213, 228};
    const cv::Vec3b to2 = {222, 73, 50};
    ColorChangeOperation colorChangeOperation2(from2, to2);
    // Gaussian blur
    cv::Size size(33, 33);
    GaussianBlurOperation gaussianBlurOperation(size);

    // Keep a list of all operations that should be applied on images
    std::vector<std::reference_wrapper<ImageOperation>> operations{
            colorChangeOperation1,
            colorChangeOperation2,
            gaussianBlurOperation
    };

    // Determine whether we want to use buffered IO or not
    bool buffered = false;
    if (argc >= 5 && std::string(argv[4]) == "-b") {
        buffered = true;
    }

    // Run in sequential mode
    if (argc >= 4 && std::string(argv[3]) == "-s") {
        return seq.run(operations, buffered);
    }

    // Run in parallel mode
    return par.run(from1, to1, buffered);
}