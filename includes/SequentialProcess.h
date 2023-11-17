//
// Created by jtag on 11/17/23.
//

#ifndef MASS_IMAGE_PROCESSING_SEQUENTIALPROCESS_H
#define MASS_IMAGE_PROCESSING_SEQUENTIALPROCESS_H

#include <filesystem>

namespace fs = std::filesystem;

class SequentialProcess {
public:
    SequentialProcess(fs::path input, fs::path output);

    int run();

private:
    const fs::path _input;
    const fs::path _output;
};


#endif //MASS_IMAGE_PROCESSING_SEQUENTIALPROCESS_H
