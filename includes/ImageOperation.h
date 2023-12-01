//
// Created by jtag on 12/1/23.
//

#ifndef MASS_IMAGE_PROCESSING_IMAGEOPERATION_H
#define MASS_IMAGE_PROCESSING_IMAGEOPERATION_H

/**
 * Base class for holding data about image operations.
 */
class ImageOperation {
public:
    /**
     * Supported operations.
     */
    enum class Operation {
        ColorChange, GaussianBlur
    };

    /**
     * Get type of current operation. This operation type will be set by child classes.
     * @return Operation type of current object.
     */
    [[nodiscard]] Operation getOperation() const {
        return _operation;
    }

protected:
    /**
     * Constructs the basic structure of any image operation.
     * @param operation Operation type.
     */
    explicit ImageOperation(Operation operation) : _operation(operation) {}

private:
    /**
     * Holds current operation type.
     */
    const Operation _operation;
};


#endif //MASS_IMAGE_PROCESSING_IMAGEOPERATION_H
