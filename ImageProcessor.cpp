#include "ImageProcessor.h"
#include "EncodeMessage.h"
#include "DecodeMessage.h"
#include <iostream>

ImageProcessor::ImageProcessor() {

}

ImageProcessor::~ImageProcessor() {

}

std::string ImageProcessor::decodeHiddenMessage(const ImageMatrix &img) {
    ImageSharpening sharpening;
    EdgeDetector edgeDetector;
    DecodeMessage decoder;
    ImageMatrix sharpenedImage = sharpening.sharpen(img,2.0);
    std::vector<std::pair<int, int>> edgePixels = edgeDetector.detectEdges(sharpenedImage);
    std::string decodedMessage = decoder.decodeFromImage(sharpenedImage, edgePixels);
    
    return decodedMessage;
}

ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix &img, const std::string &message) {
    EdgeDetector edgeDetector;
    EncodeMessage encoder;
    std::vector<std::pair<int, int>> edgePixels = edgeDetector.detectEdges(img);
    ImageMatrix encodedImage = encoder.encodeMessageToImage(img, message, edgePixels);

    return encodedImage;
}
