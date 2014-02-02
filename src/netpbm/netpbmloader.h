#ifndef __NET_PBM_LOADER_H__
#define __NET_PBM_LOADER_H__

#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <ctime>

#include "vec3.h"
#include "pgmimage.h"
#include "ppmimage.h"

#define COLOR_LEVELS 255

struct s_NetPBMFileDesc {
	unsigned int length;
	unsigned int width;
	unsigned int colors;
	unsigned char* memblock;
};

class NetPBMLoader {
    public:
        NetPBMLoader() {};
        ~NetPBMLoader() {};
        PGMImage LoadPGM(std::string filename);
        PPMImage LoadPPM(std::string filename);
        void SavePGM(PGMImage& pgmimage, std::string filename);
        void SavePPM(PPMImage& ppmimage, std::string filename);

    private:
        void Read(std::string filename, std::string ext, s_NetPBMFileDesc* fileDesc);
};

#endif
