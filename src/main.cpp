#include <iostream>
#include "config.h"
#include "renderer.h"
#include "sceneparser.h"
#include "scene.h"

int main(int argc, char** argv) {
    if(argc < 3) {
        cerr << "Abort: Must specify scene file and sppxl" << endl;
        return -1;
    }

    string scenefile(argv[1]);

    SceneParser parser(scenefile);
    Scene *scene = parser.BuildScene();

    PPMImage *film = scene->GetCamera()->Film();
    Renderer renderer(atoi(argv[2]));
    renderer.Init(*film);

    const clock_t begin = clock();
    renderer.Render(scene);
    cout << "Time: " << (double)(clock() - begin) / CLOCKS_PER_SEC << "s." << endl;

    NetPBMLoader loader;
    loader.SavePPM(*film, "image");

    delete scene;

    return 0;
}
