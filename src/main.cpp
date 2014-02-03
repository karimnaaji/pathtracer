#include <iostream>
#include "renderer.h"
#include "scene.h"

using namespace std;

int main(int argc, char** argv) {
    Vec3 cp = Vec3(3.0, 2.0, 4.0);
    Camera cam(cp);
    cam.LookAt(Vec3(0.0));

    Scene* scene = new Scene(cam);
    Renderer* renderer = new Renderer();

    Vec3 O = Vec3::Zero();

    Vec3 b = Vec3(100, 100, 255);
    Object* sphere = new Sphere(O, b, O);
    Vec3 T = Vec3(0.0, -0.2, -0.3);
    sphere->transform = Matrix4::CreateTranslation(T);
    scene->AddObject(sphere);

    Vec3 g = Vec3(100, 100, 100);
    sphere = new Sphere(O, g, O);
    T = Vec3(0.0, -0.2, 0.3);
    sphere->transform = Matrix4::CreateTranslation(T);
    scene->AddObject(sphere);

    Vec3 r = Vec3(255, 100, 100);
    Object* plane = new Plane(O, r, O);
    scene->AddObject(plane);

    cout << "Rendering.." << endl;
    const clock_t begin = clock();
    renderer->Render(scene);
    cout << "Time: " << (float)(clock() - begin) /  CLOCKS_PER_SEC << "s." << endl;

    delete scene;
    delete renderer;

    return 0;
}
