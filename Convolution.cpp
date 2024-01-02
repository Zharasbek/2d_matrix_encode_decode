#include <iostream>
#include <cmath>

#include "Convolution.h"


// Default constructor 
Convolution::Convolution() {
    kernelHeight = 0;
    kernelWidth = 0;
    stride = 1;
    padding = false;
    kernel = nullptr;
}

// Parametrized constructor for custom kernel and other parameters
Convolution::Convolution(double** customKernel, int kh, int kw, int stride_val, bool pad){
    kernelHeight = kh;
    kernelWidth = kw;
    stride = stride_val;
    padding = pad;
    this->kernel = new double*[kh];
    for(int i = 0; i < kh; i++) {
        this->kernel[i] = new double[kw];
        for(int j = 0; j < kw; j++) {
            this->kernel[i][j] = customKernel[i][j];
        }
    }

}

// Destructor
Convolution::~Convolution() {
    if (kernel != nullptr) {
            for (int i = 0; i < kernelHeight; ++i) {
                delete[] kernel[i];
            }
            delete[] kernel;
        }
        
}

// Copy constructor
Convolution::Convolution(const Convolution &other){
    kernelHeight = other.kernelHeight;
    kernelWidth = other.kernelWidth;
    stride = other.stride;
    padding = other.padding;

    kernel = new double*[kernelHeight];
    for (int i = 0; i < kernelHeight; ++i) {
        kernel[i] = new double[kernelWidth];
        for (int j = 0; j < kernelWidth; ++j) {
            kernel[i][j] = other.kernel[i][j];
        }
    }
}

// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {
    if (this == &other) {
        return *this;
    }

    // Deep copy of member variables
    if (kernel != nullptr) {
        for (int i = 0; i < kernelHeight; ++i) {
            delete[] kernel[i];
        }
        delete[] kernel;
    }

    kernelHeight = other.kernelHeight;
    kernelWidth = other.kernelWidth;
    stride = other.stride;
    padding = other.padding;

    kernel = new double*[kernelHeight];
    for (int i = 0; i < kernelHeight; ++i) {
        kernel[i] = new double[kernelWidth];
        for (int j = 0; j < kernelWidth; ++j) {
            kernel[i][j] = other.kernel[i][j];
        }
    }

    return *this;
}


// Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.
ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {
    int outputHeight, outputWidth;

    if (padding) {
        // Calculate output dimensions with padding
        outputHeight = (input_image.get_height() - kernelHeight + 2) / stride + 1;
        outputWidth = (input_image.get_width() - kernelWidth + 2) / stride + 1;
    } else {
        // Calculate output dimensions without padding
        outputHeight = (input_image.get_height() - kernelHeight) / stride + 1;
        outputWidth = (input_image.get_width() - kernelWidth) / stride + 1;
    }   

    int paddedHeight = outputHeight+2;
    int paddedWidth = outputWidth+2;
    
    ImageMatrix padded_image(paddedHeight, paddedWidth);
    ImageMatrix output_image(outputHeight, outputWidth);

    if(padding == true) {
        for(int i = 0; i < paddedHeight; i++) {
            for(int j = 0; j < paddedWidth; j++) {
                if(i == 0 || i == paddedHeight - 1 || j == 0 || j == paddedWidth - 1) {
                    continue;
                } else {
                    padded_image.set_data(i, j, input_image.get_data(i - 1, j - 1));
                }
            }
        }

        for(int i = 0; i < outputHeight; i+=stride) {
            for(int j = 0; j < outputWidth; j+=stride) {
                double sum = 0.0;
                for(int x = 0; x < kernelHeight; x++) {
                    for(int y = 0; y < kernelWidth; y++) {
                        int rowIndex = i + x;
                        int columnIndex = j + y;

                        if(rowIndex >= 0 && rowIndex < paddedHeight && columnIndex >= 0 && columnIndex < paddedWidth){
                            sum += padded_image.get_data(rowIndex, columnIndex) * kernel[x][y];
                        }
                    }
                }
                output_image.set_data(i, j, sum);
            }
        }
    } else {
        for (int i = 0; i < outputHeight; i++) {
            for (int j = 0; j < outputWidth; j++) {
                double sum = 0.0;
                for (int m = 0; m < kernelHeight; m++) {
                    for (int n = 0; n < kernelWidth; n++) {
                        int rowIndex = i * stride + m;
                        int colIndex = j * stride + n;
                        double pixelValue = 0.0;
                        pixelValue = (rowIndex >= 0 && rowIndex < input_image.get_height() && colIndex >= 0 && colIndex < input_image.get_width()) ?
                                        input_image.get_data(rowIndex, colIndex) : 0.0;
                        
                        
                        sum += pixelValue * kernel[m][n];
                    }
                }
                output_image.set_data(i, j, sum);
            }
        }
    }
    return output_image;
}

