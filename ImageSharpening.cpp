#include "ImageSharpening.h"
#include <iostream>

// Default constructor
ImageSharpening::ImageSharpening() {
    k = 1;
    kernelSize = 3;
    blurKernel = new double*[kernelSize];
    for (int i = 0; i < kernelSize; ++i) {
        blurKernel[i] = new double[kernelSize];
        for (int j = 0; j < kernelSize; ++j) {
            blurKernel[i][j] = 1.0 / 9.0;
        }
    }
}

ImageSharpening::~ImageSharpening(){
    if (blurKernel != nullptr) {
        for (int i = 0; i < kernelSize; ++i) {
            delete[] blurKernel[i];
        }
        delete[] blurKernel;
    }
}

ImageMatrix ImageSharpening::sharpen(const ImageMatrix& input_image, double k) {
    Convolution convolution(blurKernel, kernelSize, kernelSize, 1, true);

    ImageMatrix noisyImage = convolution.convolve(input_image);

    int height = input_image.get_height();
    int width = input_image.get_width();
    ImageMatrix sharpImage(height, width);

    ImageMatrix tempImage = input_image-noisyImage;
    ImageMatrix multiplied = tempImage*k;
    sharpImage = input_image+multiplied;
    sharpImage.clipValues();

    return sharpImage;
}
