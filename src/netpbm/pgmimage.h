#ifndef __PGM_IMAGE_H__
#define __PGM_IMAGE_H__

#include <string>

class PGMImage {
    public:
        PGMImage();
        PGMImage(int width, int height);
        PGMImage(const PGMImage& image);
        PGMImage& operator=(const PGMImage& image);
        ~PGMImage();
    
        float operator()(int i, int j) const;
        float& operator()(int i, int j);
        int GetHeight() const;
        int GetWidth() const;

        void Threshold(float threshold, float newValue);
    private:
        int height;
        int width;
        float* data;
};

#endif
