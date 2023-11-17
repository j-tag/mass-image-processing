//
// Created by jtag on 11/17/23.
//

#include <utility>
#include <iostream>
#include "includes/ParallelProcess.h"

ParallelProcess::ParallelProcess(fs::path input, fs::path output) : _input(std::move(input)),
                                                                    _output(std::move(output)) {}

int ParallelProcess::run(const Vec3b &find, const Vec3b &replace) {

    // Load images
    this->loadImages();

    // Perform color manipulation
    this->performColorManipulation(find, replace);

    // Save images
    this->saveImages();

    return EXIT_SUCCESS;
}

void ParallelProcess::loadImages() {
    // Queue images for read
    for (const auto &entry: fs::directory_iterator(_input)) {
        _imagesLoad.emplace(std::make_unique<Image>(entry.path()));
        _loadFutures.emplace(std::async(std::launch::async, &Image::load, _imagesLoad.back().get()));
    }

    // Load images asynchronously
    for (const auto &entry: fs::directory_iterator(_input)) {
        std::cout << "Loading: " << entry.path() << std::endl;
        _loadFutures.front().wait();
        _loadFutures.pop();
    }
}

void ParallelProcess::performColorManipulation(const Vec3b &find, const Vec3b &replace) {
    // Queue images for color manipulation
    for (const auto &entry: fs::directory_iterator(_input)) {
        std::cout << "Queuing: " << entry.path() << std::endl;
        _images.push_back(std::move(_imagesLoad.front()));
        _imagesLoad.pop();
        // Asynchronously change the color of the image
        _changeColorFutures.push(
                std::async(std::launch::async, &Image::changeColor, _images.back().get(), find, replace));
    }

    // Wait for color manipulation to be finished
    for (const auto &image: _images) {
        std::cout << "Processing: " << image->getPath() << std::endl;
        // Get the results when ready
        _changeColorFutures.front().wait();
        _changeColorFutures.pop();
    }
}

void ParallelProcess::saveImages() {
    // Save images asynchronously
    for (const auto &image: _images) {
        // Generate output file path
        const auto outputPath = _output / image->getPath().filename();
        // Save image on disk asynchronously
        _saveFutures.push(std::async(std::launch::async, &Image::save, image.get(), outputPath));
    }

    // Wait for all images to be saved on disk
    for (const auto &image: _images) {
        std::cout << "Saving: " << image->getPath() << std::endl;
        _saveFutures.front().wait();
        _saveFutures.pop();
    }
}
