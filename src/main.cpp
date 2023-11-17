#include <iostream>
#include <opencv2/core.hpp>
#include "includes/ParallelProcess.h"
#include "includes/SequentialProcess.h"


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
    const cv::Vec3b from = {190, 190, 190};
    const cv::Vec3b to = {85, 85, 255};

    bool buffered = false;
    if (argc >= 5 && std::string(argv[4]) == "-b") {
        buffered = true;
    }

    if (argc >= 4 && std::string(argv[3]) == "-s") {
        return seq.run(from, to, buffered);
    }

    return par.run(from, to, buffered);
}