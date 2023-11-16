#include <iostream>
#include <future>
#include <opencv4/opencv2/imgcodecs.hpp>
#include "Image.h"

int main(int argc, char const **argv) {
    using namespace cv;

    if (argc != 3) {
        std::cerr << "Usage: mass_image_processing <input_dir> <output_dir>\n";
        return EXIT_FAILURE;
    }

    Mat img = imread(argv[1]);
    Image image(img);
    const Vec3b from = {190, 190, 190};
    const Vec3b to = {85, 85, 255};
    // Asynchronously change the color of the image
    std::future<void> changeColorFuture = std::async(std::launch::async, &Image::changeColor, &image, from, to);

    // Get the results when ready
    changeColorFuture.get();
    // Save image on disk
    image.save(argv[2]);

    return EXIT_SUCCESS;
}