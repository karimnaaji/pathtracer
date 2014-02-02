#include "netpbmloader.h"

void NetPBMLoader::Read(std::string filename, std::string ext, s_NetPBMFileDesc* fileDesc) {
    std::string path = filename + ext;
    std::string line1;
    std::string line2;
    std::ifstream file(path.c_str(), std::ios::in | std::ios::binary);
    std::ifstream::pos_type start, end, size;
    std::ifstream::off_type newStart;
    
    if(!file) {
        std::cerr << "Error while opening " << path << std::endl;
        throw std::runtime_error("Can't open file" + path);
    }   

    std::cout << "Reading " << path << std::endl;

    getline(file, line1);
    start = file.tellg();
    getline(file, line2);

    std::cout << "Header: " << std::endl;
    std::cout << line1 << std::endl;

    if(line2[0] != '#') {
        file.seekg(start, std::ios::beg);
    } else {
        std::cout << line2 << std::endl;
    }

    file >> fileDesc->length;
    file >> fileDesc->width;
    file >> fileDesc->colors;

    std::cout << " - Width: " << fileDesc->width << ", Length: " << fileDesc->length << std::endl;
    std::cout << " - Colors: " << fileDesc->colors << std::endl;

    start = file.tellg();
    file.seekg (0, std::ios::end);
    end = file.tellg();
    size = end - start;

    char* memblock = new char[size];
    newStart = static_cast<std::ifstream::off_type>(start);
    file.seekg(newStart+1, std::ios::beg);
    file.read(memblock, size);
    file.close();

    fileDesc->memblock = (unsigned char*)memblock;
}

PGMImage NetPBMLoader::LoadPGM(std::string filename) { 
    s_NetPBMFileDesc* fileDesc = new s_NetPBMFileDesc();
    Read(filename, ".pgm", fileDesc);   
    PGMImage image(fileDesc->length, fileDesc->width);

    for(int i = 0; i < image.GetWidth(); ++i) {
        for(int j = 0; j < image.GetHeight(); ++j) {
            image(i, j) = (float)(fileDesc->memblock[i*image.GetWidth()+j]);
        }   
    }

    delete[] fileDesc->memblock;
    delete fileDesc;

    return image;
}

PPMImage NetPBMLoader::LoadPPM(std::string filename) {
    s_NetPBMFileDesc* fileDesc = new s_NetPBMFileDesc();
    Read(filename, ".ppm", fileDesc);
    PPMImage image(fileDesc->length, fileDesc->width);
    const int nbChannels = 3;

    for(int i = 0; i < image.GetWidth(); ++i) {
        for(int j = 0; j < image.GetHeight()*nbChannels; j+=3) {
            Vec3 color;
            color.r = (float)(fileDesc->memblock[i*image.GetWidth()*nbChannels+j]);
            color.g = (float)(fileDesc->memblock[i*image.GetWidth()*nbChannels+j+1]);
            color.b = (float)(fileDesc->memblock[i*image.GetWidth()*nbChannels+j+2]);
            image(i, j/nbChannels) = color;
        }   
    }

    delete[] fileDesc->memblock;
    delete fileDesc;

    return image;
}


void NetPBMLoader::SavePGM(PGMImage& pgmimage, std::string filename) {
    std::string path = filename + ".pgm";
    std::ofstream file(path.c_str(), std::ios::out | std::ios::binary);

    if(file.is_open()) {
        time_t now = time(0);
        char* dt = ctime(&now);

        file << "P5\n";
        file << "# " << dt;
        file << pgmimage.GetWidth() << " " << pgmimage.GetHeight() << "\n";
        file << COLOR_LEVELS << "\n";

        for(int j = 0; j < pgmimage.GetHeight(); ++j) {
            for(int i = 0; i < pgmimage.GetWidth(); ++i) {
                file << (char)(pgmimage(i, j));
            }
        }

        file.close();
        std::cout << "Saved file " << path << std::endl;
    }
}

void NetPBMLoader::SavePPM(PPMImage& pgmimage, std::string filename) {
    std::string path = filename + ".ppm";
    std::ofstream file(path.c_str(), std::ios::out | std::ios::binary);

    if(file.is_open()) {
        time_t now = time(0);
        char* dt = ctime(&now);

        file << "P6\n";
        file << "# " << dt;
        file << pgmimage.GetWidth() << " " << pgmimage.GetHeight() << "\n";
        file << COLOR_LEVELS << "\n";

        for(int j = 0; j < pgmimage.GetHeight(); ++j) {
            for(int i = 0; i < pgmimage.GetWidth(); ++i) {
                file << (char)(pgmimage(i, j).r);
                file << (char)(pgmimage(i, j).g);
                file << (char)(pgmimage(i, j).b);
            }
        }

        file.close();
        std::cout << "Saved file " << path << std::endl;
    }
}

