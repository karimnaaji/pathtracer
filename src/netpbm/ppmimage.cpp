#include "ppmimage.h"

PPMImage::PPMImage() :  
    height(0),
    width(0) { 
    data = NULL;
}

PPMImage::PPMImage(int width_, int height_) : 
    height(height_), 
    width(width_) {
    data = new Vec3*[height];
    for(int j = 0; j < height; ++j) {
        data[j] = new Vec3[width];
    }

    for(int i = 0; i < width; ++i) {
        for(int j = 0; j < height; ++j) {
            (*this)(i,j) = Vec3::Zero();
        }
    }
}

PPMImage::PPMImage(const PPMImage& image) {
    height = image.height;
    width = image.width;
    data = new Vec3*[height];
    for(int j = 0; j < height; ++j) {
        data[j] = new Vec3[width];
    }

    for(int i = 0; i < width; ++i) {
        for(int j = 0; j < height; ++j) {
            (*this)(i,j) = image(i,j);
        }
    }
}

PPMImage& PPMImage::operator=(const PPMImage& image) {
    if(this != &image) {
        if(data != NULL) {
            for(int j = 0; j < height; ++j) 
                delete[] data[j];
            delete[] data;
        }
        height = image.height;
        width = image.width;

        data = new Vec3*[height];
        for(int i = 0; i < width; ++i) {
            data[i] = new Vec3[width];
        }
        for(int i = 0; i < width; ++i) {
            for(int j = 0; j < height; ++j) {
                (*this)(i,j) = image(i,j);
            }
        }
    }
    return *this;
}

PPMImage::~PPMImage() {
    if(data != NULL) {
        for(int j = 0; j < height; ++j) 
            delete[] data[j];
        delete[] data;
    }
}

Vec3 PPMImage::operator()(int i, int j) const {
    return data[j][i];
}

Vec3& PPMImage::operator()(int i, int j) {
    return data[j][i];
}

int PPMImage::GetHeight() const {
    return height;
}

int PPMImage::GetWidth() const {
    return width;
}

int PPMImage::GetSize() const {
    return width*height;
}
