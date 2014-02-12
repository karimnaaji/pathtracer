#ifndef __SCENE_PARSER_H__
#define __SCENE_PARSER_H__

#include <fstream>
#include <sstream>
#include "scene.h"
#include "object.h"
#include "sphere.h"
#include "plane.h"
#include "config.h"

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
