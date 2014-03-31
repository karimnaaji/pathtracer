#ifndef __SHADING_H__
#define __SHADING_H__

#include "scene.h"
#include "helpers.h"

Color AverageColor(Scene *scene, float x, float y, float pxw, float pxh, int aadepth, int sppxl);
Color Ri(Scene *scene, const Ray& ray, int depth, const Vec2 &pixelPos, Object *caller = NULL);

#endif
