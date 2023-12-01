//
// Created by jtag on 11/16/23.
//

#ifndef MASS_IMAGE_PROCESSING_IMAGE_H
#define MASS_IMAGE_PROCESSING_IMAGE_H

#include <opencv2/imgcodecs.hpp>
#include <filesystem>

using namespace cv;
namespace fs = std::filesystem;

/**
 * Our custom data structure to manipulate OpenCV images in a fast and performant way.
 */
class Image {
public:
    /**
     * Constructs a manipulated OpenCV image.
     * @param path Image path.
     */
    explicit Image(fs::path path);

    /**
     * Loads the image from constructor path to OpenCV.
     */
    void load();

    /**
     * Loads the image from constructor path to OpenCV with buffered IO.
     */
    void loadBuffered();

    /**
     * Perform a color change operation using OpenCV and parallel execution policy.
     * @param find The color to be found.
     * @param replace The color that should be replaced with the founded color.
     */
    void changeColor(const Vec3b &find, const Vec3b &replace);

    /**
     * Perform a gaussian blur operation using OpenCV and TDD parallel loops.
     * @param size The size of gaussian blur to be applied.
     */
    void gaussianBlur(const Size &size);

    /**
     * Saves current OpenCV image to provided path.
     * @param filename The path to save new file.
     */
    void save(const String &filename);

    /**
     * Saves current OpenCV image to provided path using buffered IO.
     * @param filename
     */
    void saveBuffered(const String &filename);

    /**
     * Returns the loaded image path.
     * @return Image path.
     */
    [[nodiscard]] fs::path getPath() const;

private:
    /**
     * Holds OpenCV image.
     */
    Mat _img;

    /**
     * Holds the loaded image path.
     */
    const fs::path _path;
};


#endif //MASS_IMAGE_PROCESSING_IMAGE_H
