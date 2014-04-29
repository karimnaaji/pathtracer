#ifndef __PGM_IMAGE_H__
#define __PGM_IMAGE_H__

#include <string>
#include "image.h"

class PGMImage : public Image<float> {
    public:
        PGMImage();
        PGMImage(int width, int height);
        PGMImage(const PGMImage& image);
        PGMImage& operator=(const PGMImage& image);
        ~PGMImage();
    
        float operator()(int i, int j) const;
        float& operator()(int i, int j);

        void Threshold(float threshold, float newValue);
    private:
        float* data;
};

#endif
