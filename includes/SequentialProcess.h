//
// Created by jtag on 11/17/23.
//

#ifndef MASS_IMAGE_PROCESSING_SEQUENTIALPROCESS_H
#define MASS_IMAGE_PROCESSING_SEQUENTIALPROCESS_H

#include <filesystem>
#include "ImageOperation.h"
#include "ColorChangeOperation.h"

namespace fs = std::filesystem;
using namespace cv;

/**
 * Use this class to run image operations sequentially. This class will not use any concurrency at all.
 */
class SequentialProcess {
public:
    /**
     * Constructs a sequential execution receiving input and output directories of images.
     * @param input Input directory should contains as many as jpg images you want.
     * @param output Output directory should be empty. Modified images will be placed here.
     */
    SequentialProcess(fs::path input, fs::path output);

    /**
     * Runs the manipulation process sequentially.
     * @param operations A list of image operations to be applied to all images.
     * @param buffered Whether to use buffered IO or not.
     * @return Returns `EXIT_SUCCESS` when finished ok.
     */
    int run(const std::vector<std::reference_wrapper<ImageOperation>> &operations, bool buffered);

private:
    /**
     * Changes color of an OpenCV images sequentially using details provided by a `ColorChangeOperation` object.
     * @param img
     * @param operation
     */
    static void colorChange(cv::Mat &img, const ColorChangeOperation &operation);

    /**
     * Input directory. Should contains jpg images.
     */
    const fs::path _input;

    /**
     * Output directory. Should be empty.
     */
    const fs::path _output;
};


#endif //MASS_IMAGE_PROCESSING_SEQUENTIALPROCESS_H
