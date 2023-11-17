//
// Created by jtag on 11/17/23.
//

#ifndef MASS_IMAGE_PROCESSING_PARALLELPROCESS_H
#define MASS_IMAGE_PROCESSING_PARALLELPROCESS_H

#include <filesystem>

namespace fs = std::filesystem;

class ParallelProcess {
public:
    ParallelProcess(fs::path input, fs::path output);

    int run();

private:
    const fs::path _input;
    const fs::path _output;
};


#endif //MASS_IMAGE_PROCESSING_PARALLELPROCESS_H
