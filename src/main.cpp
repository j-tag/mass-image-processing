#include <iostream>
#include <opencv4/opencv2/core.hpp>
#include "includes/ParallelProcess.h"
#include "includes/SequentialProcess.h"


int main(int argc, char const **argv) {

    if (argc < 3 || argc > 4) {
        std::cerr << "Usage: mass_image_processing <input_dir> <output_dir> [-p,-s]\n"
                     "-p: parallel processing (default)\n"
                     "-s: sequential processing\n";
        return EXIT_FAILURE;
    }

    ParallelProcess p(argv[1], argv[2]);
    SequentialProcess s(argv[1], argv[2]);

    // Color manipulation values
    const cv::Vec3b from = {190, 190, 190};
    const cv::Vec3b to = {85, 85, 255};

    if (argc == 4 && std::string(argv[3]) == "-s") {
        return s.run(from, to);
    }
    return p.run(from, to);
}