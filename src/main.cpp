#include <iostream>
#include "renderer.h"
#include "scene.h"
#include "sceneparser.h"

using namespace std;

int main(int argc, char** argv) {
    string scenefile(argv[1]);
    SceneParser parser(scenefile);

    Scene* scene = parser.BuildScene();
    Renderer* renderer = new Renderer();

    const clock_t begin = clock();
    renderer->Render(scene, Vec2(1280, 720));
    cout << "Time: " << (double)(clock() - begin) / CLOCKS_PER_SEC << "s." << endl;

    delete scene;
    delete renderer;

    return 0;
}
