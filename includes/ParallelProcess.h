//
// Created by jtag on 11/17/23.
//

#ifndef MASS_IMAGE_PROCESSING_PARALLELPROCESS_H
#define MASS_IMAGE_PROCESSING_PARALLELPROCESS_H

#include <future>
#include <queue>
#include <filesystem>
#include "includes/Image.h"
#include "ImageOperation.h"

namespace fs = std::filesystem;

/**
 * Use this class to run image operations concurrently and efficiently utilizing maximum power of CPU and RAM.
 */
class ParallelProcess {
public:
    /**
     * Constructs a parallel execution receiving input and output directories of images.
     * @param input Input directory should contains as many as jpg images you want.
     * @param output Output directory should be empty. Modified images will be placed here.
     */
    ParallelProcess(fs::path input, fs::path output);

    /**
     * Runs the manipulation process concurrently and efficiently.
     * @param operations A list of image operations to be applied to all images.
     * @param buffered Whether to use buffered IO or not.
     * @return Returns `EXIT_SUCCESS` when finished ok.
     */
    int run(const std::vector<std::reference_wrapper<ImageOperation>> &operations, bool buffered);

private:
    /**
     * Loads all images from input directory to OpenCV concurrently.
     * @param buffered Whether to use buffered IO or not.
     */
    void loadImages(bool buffered);

    /**
     * Performs all of the image manipulation processes concurrently and efficiently in parallel preserving their order.
     * @param operations A list of image operations to be applied to all images.
     */
    void performOperations(const std::vector<std::reference_wrapper<ImageOperation>> &operations);

    /**
     * Saves all images to output directory using OpenCV concurrently.
     * @param buffered
     */
    void saveImages(bool buffered);

private:
    /**
     * Input directory. Should contains jpg images.
     */
    const fs::path _input;

    /**
     * Output directory. Should be empty.
     */
    const fs::path _output;

    /**
     * A queue of futures to perform OpenCV manipulation operations in parallel.
     */
    std::queue<std::future<void>> _operationsFutures;

    /**
     * A queue of futures to load images in parallel.
     */
    std::queue<std::future<void>> _loadFutures;

    /**
     * A queue of futures to save images in parallel.
     */
    std::queue<std::future<void>> _saveFutures;

    /**
     * A queue of smart pointers to load images to OpenCV in parallel.
     */
    std::queue<std::unique_ptr<Image>> _imagesLoad;

    /**
     * A vector of smart pointers to hold and manipulate images in parallel.
     */
    std::vector<std::unique_ptr<Image>> _images;
};


#endif //MASS_IMAGE_PROCESSING_PARALLELPROCESS_H
