#include <iostream>
#include "renderer.h"
#include "scene.h"

using namespace std;

int main(int argc, char** argv) {
    Vec3 cp = Vec3(-0.7, 2.0, -3.0);
    Camera cam(cp);
    cam.LookAt(Vec3(-1.0, 1.0, -1.0));

    Scene* scene = new Scene(cam);
    Renderer* renderer = new Renderer();

    Vec3 O = Vec3::Zero();

    Vec3 b = Vec3(0.5, 0.5, 0.6);
    Object *sphere1 = new Sphere(Vec3(-2.0, 1.0, 0.0), b, O);
    sphere1->material = E_SPECULAR;
    scene->AddObject(sphere1);

    Object *sphere3 = new Sphere(Vec3(-3.0, 1.5, -2.0), b * 0.5, O);
    sphere3->material = E_SPECULAR;
    scene->AddObject(sphere3);

    Vec3 g = Vec3(0.5, 1.0, 0.5);
    Object *sphere2 = new Sphere(Vec3(0.0, 1.0, 0.0), g, O);
    sphere2->material = E_DIFFUSE;
    scene->AddObject(sphere2);

    Vec3 r = Vec3(1.0, 0.5, 0.5);
    Object* plane = new Plane(O, r, O);
    plane->material = E_DIFFUSE;
    scene->AddObject(plane);

    cout << "Rendering.." << endl;
    const clock_t begin = clock();
    renderer->Render(scene);
    cout << "Time: " << (float)(clock() - begin) / CLOCKS_PER_SEC << "s." << endl;

    delete scene;
    delete renderer;

    return 0;
}
