//
// Created by jtag on 11/17/23.
//

#include <utility>
#include <future>
#include <queue>
#include <iostream>
#include "includes/Image.h"
#include "includes/ParallelProcess.h"

ParallelProcess::ParallelProcess(fs::path input, fs::path output) : _input(std::move(input)),
                                                                    _output(std::move(output)) {}

int ParallelProcess::run() {

    std::queue<std::future<void>> changeColorFutures;
    std::queue<std::future<void>> loadFutures;
    std::queue<std::future<void>> saveFutures;
    std::vector<std::unique_ptr<Image>> images;
    std::queue<std::unique_ptr<Image>> imagesLoad;
    // Color manipulation values
    const Vec3b from = {190, 190, 190};
    const Vec3b to = {85, 85, 255};

    // Queue images for read
    for (const auto &entry: fs::directory_iterator(_input)) {
        imagesLoad.emplace(std::make_unique<Image>(entry.path()));
        loadFutures.emplace(std::async(std::launch::async, &Image::load, imagesLoad.back().get()));
    }

    // Load images asynchronously
    for (const auto &entry: fs::directory_iterator(_input)) {
        std::cout << "Loading: " << entry.path() << std::endl;
        loadFutures.front().wait();
        loadFutures.pop();
    }

    // Queue images for color manipulation
    for (const auto &entry: fs::directory_iterator(_input)) {
        std::cout << "Queuing: " << entry.path() << std::endl;
        images.push_back(std::move(imagesLoad.front()));
        imagesLoad.pop();
        // Asynchronously change the color of the image
        changeColorFutures.push(std::async(std::launch::async, &Image::changeColor, images.back().get(), from, to));
    }

    // Wait for color manipulation to be finished
    for (const auto &image: images) {
        std::cout << "Processing: " << image->getPath() << std::endl;
        // Get the results when ready
        changeColorFutures.front().wait();
        changeColorFutures.pop();
    }

    // Save images asynchronously
    for (const auto &image: images) {
        // Generate output file path
        const auto outputPath = _output / image->getPath().filename();
        // Save image on disk asynchronously
        saveFutures.push(std::async(std::launch::async, &Image::save, image.get(), outputPath));
    }

    // Wait for all images to be saved on disk
    for (const auto &image: images) {
        std::cout << "Saving: " << image->getPath() << std::endl;
        saveFutures.front().wait();
        saveFutures.pop();
    }

    return EXIT_SUCCESS;
}
