// EdgeDetector.cpp

#include "EdgeDetector.h"
#include <iostream>
#include <cmath>

EdgeDetector::EdgeDetector() {
    gX = new double*[3];
    gY = new double*[3];

    for(int i = 0; i < 3; i++) {
        gX[i] = new double[3];
        gY[i] = new double[3];
    }

    // Initialize the Sobel operators
    gX[0] = new double[3]{-1.0, 0.0, 1.0};
    gX[1] = new double[3]{-2.0, 0.0, 2.0};
    gX[2] = new double[3]{-1.0, 0.0, 1.0};

    gY[0] = new double[3]{-1.0, -2.0, -1.0};
    gY[1] = new double[3]{0.0, 0.0, 0.0};
    gY[2] = new double[3]{1.0, 2.0, 1.0};
}

EdgeDetector::~EdgeDetector() {
    for(int i = 0; i < 3; i++) {
        delete[] gX[i];
        delete[] gY[i];
    }

    delete[] gX;
    delete[] gY;
}

// Detect Edges using the given algorithm
std::vector<std::pair<int, int>> EdgeDetector::detectEdges(const ImageMatrix& input_image) {
    std::vector<std::pair<int, int>> edgePixels;

    Convolution verticalCon(gY, 3, 3, 1, true);
    Convolution horizontalCon(gX, 3, 3, 1, true);

    int inputImgHeight = input_image.get_height();
    int inputImgWidth = input_image.get_width();

    ImageMatrix verticalDerivative = verticalCon.convolve(input_image);
    ImageMatrix horizontalDerivative = horizontalCon.convolve(input_image);

    ImageMatrix gradient(verticalDerivative.get_height(), verticalDerivative.get_width());

    double avg_gradient = 0.0;
    for(int i = 0; i < inputImgHeight; i++) {
        for(int j = 0; j < inputImgWidth; j++) {
            double verticalData = verticalDerivative.get_data(i, j);
            double horizontalData = horizontalDerivative.get_data(i, j);
            avg_gradient += verticalData * verticalData + horizontalData * horizontalData;
            gradient.set_data(i, j, verticalData * verticalData + horizontalData * horizontalData);
        }
    }

    avg_gradient = avg_gradient / (inputImgHeight * inputImgWidth);
        
    for(int i = 0; i < inputImgHeight; i++) {
        for(int j = 0; j < inputImgWidth; j++) {
            double verticalData = verticalDerivative.get_data(i, j);
            double horizontalData = horizontalDerivative.get_data(i, j);
            double gradient_value = verticalData * verticalData + horizontalData * horizontalData;
            if(gradient_value > avg_gradient) {
                edgePixels.push_back(std::make_pair(i,j));
            }
        }
    }


    return edgePixels;
}

