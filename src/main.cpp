#include <iostream>

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

    if (argc == 4 && std::string(argv[3]) == "-s") {
        return s.run();
    }
    return p.run();
}