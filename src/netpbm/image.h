#ifndef __IMAGE_H__
#define __IMAGE_H__

template<typename T> class Image {
    public:
        Image() {}
        Image(int width, int height) {
            this->width = width;
            this->height = height;
        }

        virtual ~Image() {}

        int GetWidth() const { return width; }
        int GetHeight() const { return height; }
        int GetSize() const { return width * height; }

        virtual T operator()(int i, int j) const = 0;
        virtual T& operator()(int i, int j) = 0;

    protected:
        int width;
        int height;
};

#endif
