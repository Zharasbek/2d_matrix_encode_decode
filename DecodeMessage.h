#ifndef DECODE_MESSAGE_H
#define DECODE_MESSAGE_H

#include <string>
#include "ImageMatrix.h"

// Class `DecodeMessage`: Provides the functionality to decode a binary message into an ASCII representation.
class DecodeMessage {
    public:
        // Constructors and destructors
        DecodeMessage(); // Default constructor
        ~DecodeMessage(); // Destructor

        std::string decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels);
    
    private:
        // Any private helper functions or variables if necessary    
};

#endif // DECODE_MESSAGE_H
