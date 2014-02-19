#ifndef __OBJ_PARSER_H__
#define __OBJ_PARSER_H__

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip> 
#include <limits>

#include "scene.h"
#include "config.h"
#include "triangle.h"

class ObjParser {
    public:
        ObjParser() {}
        void Parse(string objfile, Scene* scene, Vec3 pos, Vec3 col, Vec3 emis, MaterialType material) const;
};

#endif
