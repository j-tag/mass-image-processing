//
// Created by jtag on 11/17/23.
//

#include <utility>
#include <iostream>
#include "includes/ParallelProcess.h"
#include "includes/ColorChangeOperation.h"
#include "includes/GaussianBlurOperation.h"

ParallelProcess::ParallelProcess(fs::path input, fs::path output) : _input(std::move(input)),
                                                                    _output(std::move(output)) {}

int ParallelProcess::run(const std::vector<std::reference_wrapper<ImageOperation>> &operations, bool buffered) {

    // Load images
    this->loadImages(buffered);

    // Perform image manipulation operations
    this->performOperations(operations);

    // Save images
    this->saveImages(buffered);

    return EXIT_SUCCESS;
}

void ParallelProcess::loadImages(bool buffered) {
    // Queue images for read
    for (const auto &entry: fs::directory_iterator(_input)) {
        _imagesLoad.emplace(std::make_unique<Image>(entry.path()));
        if (buffered) {
            _loadFutures.emplace(std::async(std::launch::async, &Image::loadBuffered, _imagesLoad.back().get()));
        } else {
            _loadFutures.emplace(std::async(std::launch::async, &Image::load, _imagesLoad.back().get()));
        }
    }

    // Load images asynchronously
    for (const auto &entry: fs::directory_iterator(_input)) {
        std::cout << "Loading: " << entry.path() << std::endl;
        _loadFutures.front().wait();
        _loadFutures.pop();
    }
}

void ParallelProcess::performOperations(const std::vector<std::reference_wrapper<ImageOperation>> &operations) {
    // Queue images for manipulations
    for (const auto &entry: fs::directory_iterator(_input)) {
        std::cout << "Queuing: " << entry.path() << std::endl;
        _images.push_back(std::move(_imagesLoad.front()));
        _imagesLoad.pop();
        // Process all operations of each image asynchronously and preserve order of manipulations
        _operationsFutures.push(
                std::async(std::launch::async, &Image::orderedOperations, _images.back().get(), operations));
    }

    // Wait for all manipulations to be finished
    for (const auto &image: _images) {
        std::cout << "Processing: " << image->getPath() << std::endl;
        // Get the results when ready
        _operationsFutures.front().wait();
        _operationsFutures.pop();
    }
}

void ParallelProcess::saveImages(bool buffered) {
    // Save images asynchronously
    for (const auto &image: _images) {
        // Generate output file path
        const auto outputPath = _output / image->getPath().filename();
        // Save image on disk asynchronously
        if (buffered) {
            _saveFutures.push(std::async(std::launch::async, &Image::saveBuffered, image.get(), outputPath));
        } else {
            _saveFutures.push(std::async(std::launch::async, &Image::save, image.get(), outputPath));
        }
    }

    // Wait for all images to be saved on disk
    for (const auto &image: _images) {
        std::cout << "Saving: " << image->getPath() << std::endl;
        _saveFutures.front().wait();
        _saveFutures.pop();
    }
}
