#include <iostream>
#include "renderer.h"
#include "scene.h"

using namespace std;

int main(int argc, char** argv) {
    Vec3 cp = Vec3(0.0, 1.0, -3.0);
    Camera cam(cp);
    cam.LookAt(Vec3(1.0));

    Scene* scene = new Scene(cam);
    Renderer* renderer = new Renderer();

    Vec3 O = Vec3::Zero();
    Object* sphere = new Sphere(O, O, O);
    scene->AddObject(sphere);

    cout << "Rendering .." << endl;
    renderer->Render(scene);

    return 0;
}
