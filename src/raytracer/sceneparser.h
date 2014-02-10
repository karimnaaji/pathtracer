#ifndef __SCENE_PARSER_H__
#define __SCENE_PARSER_H__


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "object.h"
#include "scene.h"
#include "raytracer.h"

class SceneParser {
    public:
        SceneParser(string scenefile) : filename(scenefile) {}

        Scene* BuildScene() const;

    private:
        void LoadCamera(Scene* scene, const char* line) const;
        void LoadObject(Scene* scene, const char* line) const;
        string filename;
};

#endif
