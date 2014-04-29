#include "pgmimage.h"

PGMImage::PGMImage() : Image(0, 0) {
    data = NULL;
}

PGMImage::PGMImage(int width_, int height_) : Image(width_, height_) {
    data = new float[height*width];

    for(int i = 0; i < width; ++i) {
        for(int j = 0; j < height; ++j) {
            (*this)(i,j) = 0.0;
        }
    }
}

PGMImage::PGMImage(const PGMImage& image) {
    height = image.height;
    width = image.width;
    data = new float[height*width];

    for(int i = 0; i < width; ++i) {
        for(int j = 0; j < height; ++j) {
            (*this)(i,j) = image(i,j);
        }
    }
}

PGMImage& PGMImage::operator=(const PGMImage& image) {
    if(this != &image) {
        if(data != NULL) {
            delete[] data;
        }
        height = image.height;
        width = image.width;

        data = new float[height*width];
        for(int i = 0; i < width; ++i) {
            for(int j = 0; j < height; ++j) {
                (*this)(i,j) = image(i,j);
            }
        }
    }
    return *this;
}

PGMImage::~PGMImage() {
    if(data != NULL) {
        delete[] data;
    }
}

float PGMImage::operator()(int i, int j) const {
    return data[j*height+i];
}

float& PGMImage::operator()(int i, int j) {
    return data[j*height+i];
}

void PGMImage::Threshold(float threshold, float newValue) {
    for(int i = 0; i < width; ++i) {
        for(int j = 0; j < height; ++j) {
            if((*this)(i,j) > threshold) {
                (*this)(i,j) = newValue;
            }
        }
    }
}
