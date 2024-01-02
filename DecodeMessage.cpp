// DecodeMessage.cpp

#include "DecodeMessage.h"
#include <iostream>

// Default constructor
DecodeMessage::DecodeMessage() {
    // Nothing to initialize here
}

// Destructor
DecodeMessage::~DecodeMessage() {
    // Nothing to clean up
}

std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels) {
    std::string binaryString = "";

    for (const auto& pixel : edgePixels) {
        int i = pixel.first;
        int j = pixel.second;
        std::cout<<i<<" "<<image.get_data(i,j)<<std::endl;
        int lsb = static_cast<int>(image.get_data(i, j)) & 1;
        binaryString += std::to_string(lsb);
    }
    
    while (binaryString.length() % 7 != 0) {
        binaryString = "0" + binaryString;
    }

    std::string decodedMessage = "";
    for (size_t i = 0; i < binaryString.length(); i += 7) {
        std::string segment = binaryString.substr(i, 7);
        int asciiValue = std::stoi(segment, nullptr, 2);
        if (asciiValue <= 32) {
            asciiValue += 33;
        } else if (asciiValue == 127) {
            asciiValue = 126;
        }
        decodedMessage += static_cast<char>(asciiValue);
    }
    return decodedMessage;
}
