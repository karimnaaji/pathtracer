#ifndef __PPM_IMAGE_H__
#define __PPM_IMAGE_H__

#include <string>
#include <iostream>

#include "vec3.h"
#include "image.h"

class PPMImage : public Image<Vec3> {
    public:
        PPMImage();
        PPMImage(int width, int height);
        PPMImage(const PPMImage& image);
        PPMImage& operator=(const PPMImage& image);
        ~PPMImage();
    
        Vec3 operator()(int i, int j) const;
        Vec3& operator()(int i, int j);
        int GetGrayscale() const;
        float* Data() const;
    private:
        int grayscale;
        Vec3** data;
};

#endif
