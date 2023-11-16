#include <iostream>
#include <future>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <filesystem>
#include "includes/Image.h"

int main(int argc, char const **argv) {
    using namespace cv;
    namespace fs = std::filesystem;

    if (argc != 3) {
        std::cerr << "Usage: mass_image_processing <input_dir> <output_dir>\n";
        return EXIT_FAILURE;
    }

    std::string path = argv[1];
    // Loop through all files in provided directory
    for (const auto &entry: fs::directory_iterator(path)) {
        std::cout << "Processing: " << entry.path() << std::endl;
        // Load image
        Mat img = imread(entry.path());
        Image image(img);
        const Vec3b from = {190, 190, 190};
        const Vec3b to = {85, 85, 255};
        // TODO: This call should be done separately
        // Asynchronously change the color of the image
        std::future<void> changeColorFuture = std::async(std::launch::async, &Image::changeColor, &image, from, to);

        // Get the results when ready
        changeColorFuture.get();
        // Generate output file path
        std::filesystem::path outputPath = argv[2] / entry.path().filename();
        std::cout << "Done: " << outputPath << std::endl;
        // Save image on disk
        image.save(outputPath);
    }

    return EXIT_SUCCESS;
}