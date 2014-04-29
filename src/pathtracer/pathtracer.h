#ifndef __PATH_TRACER_H__
#define __PATH_TRACER_H__

#include <iostream>

#define VERSION_MAJOR 0
#define VERSION_MINOR 9
#define VERSION_MAINT 2

inline void PrintVersion() {
    std::cout << "VERSION -- " << 
        VERSION_MAJOR << "." <<
        VERSION_MINOR << "." <<
        VERSION_MAINT << std::endl;
}

inline bool CompareVersion(int vmaj, int vmin, int vmaint) {
    return VERSION_MAJOR == vmaj && 
        VERSION_MINOR == vmin && 
        VERSION_MAINT == vmaint;
}

#endif
