#include "EncodeMessage.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <bitset>

// Default Constructor
EncodeMessage::EncodeMessage() {

}

// Destructor
EncodeMessage::~EncodeMessage() {
    
}

bool EncodeMessage::is_prime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int EncodeMessage::getFibonacci(int n) {
    if (n <= 1) {
        return n;
    }

    int fib[n + 1];
    fib[0] = 0;
    fib[1] = 1;

    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    return fib[n];
}

// Function to encode a message into an image matrix
ImageMatrix EncodeMessage::encodeMessageToImage(const ImageMatrix &img, const std::string &message, const std::vector<std::pair<int, int>>& edgePixels) {
    ImageMatrix encodedImage = img;
    std::string transformedMessage = message;

    for (size_t i = 0; i < message.length(); ++i) {
        if (is_prime(i)) {
            int asciiValue = static_cast<int>(message[i]);
            int fibonacciNumber = getFibonacci(i);

            asciiValue += fibonacciNumber;

            if (asciiValue < 33) {
                asciiValue += 33;
            } else if (asciiValue > 126) {
                asciiValue = 126;
            }

            transformedMessage[i] = static_cast<char>(asciiValue);
        }
        
    }
    std::string shiftedMessage = transformedMessage;
    int shiftAmount = (message.length()+1) / 2;
    std::rotate(shiftedMessage.begin(), shiftedMessage.begin() + shiftAmount, shiftedMessage.end());

    size_t messageIndex = 0;
    for (size_t i = 0; i < edgePixels.size(); ++i) {
        int row = edgePixels[i].first;
        int col = edgePixels[i].second;

        int pixelValue = static_cast<int>(encodedImage.get_data(row, col));

        pixelValue = (pixelValue & 0xFE) | (shiftedMessage[messageIndex] ? 1 : 0);
        
        encodedImage.set_data(row, col, static_cast<double>(pixelValue));

        messageIndex = (messageIndex + 1) % shiftedMessage.size();

    }
    std::cout<<messageIndex<<std::endl;
    return encodedImage;
}





