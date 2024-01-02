#ifndef IMAGE_MATRIX_H
#define IMAGE_MATRIX_H

#include <string>

#include "ImageLoader.h"

class ImageMatrix {
public:
    // Constructors and Destructor
    ImageMatrix(); // Default constructor
    ImageMatrix(const std::string &filepath); // Parameterized constructor for loading image from file
    ImageMatrix(int imgHeight, int imgWidth); // Constructor for creating a blank image of given size
    ImageMatrix(const double** inputMatrix, int imgHeight, int imgWidth); // Parameterized constructor - direct initialization with 2D matrix
    ImageMatrix(const ImageMatrix &other); // Copy constructor
    ImageMatrix& operator=(const ImageMatrix &other); // Copy assignment operator
    ~ImageMatrix(); // Destructor

    // Overloaded operators
    ImageMatrix operator+(const ImageMatrix &other) const;
    ImageMatrix operator-(const ImageMatrix &other) const;
    ImageMatrix operator*(const double &scalar) const; // Scalar multiplication

    double** get_data() const; // Getter function to access the data in the matrix
    double get_data(int i, int j) const; // Getter function to access the data at the index (i, j)

    void set_data(int i, int j, double sum);

    int get_height() const;
    int get_width() const; 
    void clipValues();

private:
    // Private member variables to store the image data
    double** data; // 2D array to store image data
    int height; // Height of the matrix
    int width; // Width of the matrix
};

#endif // IMAGE_MATRIX_H
