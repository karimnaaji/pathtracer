#include <iostream>

#include "config.h"
#include "renderer.h"
#include "sceneparser.h"
#include "scene.h"
#include "bvh.h"

int main(int argc, char** argv) {
    if(argc < 3) {
        cerr << "Abort: Must specify scene file and sppxl" << endl;
        return -1;
    }

    string scenefile(argv[1]);

    SceneParser parser(scenefile);
    Scene *scene = parser.BuildScene();
    //BVH bvh(scene->Objects());
    //bvh.Display(bvh.root);

    PPMImage *film = scene->GetCamera()->Film();

    float data[film->GetWidth()*film->GetHeight()*3];
    for(int i = 0; i < film->GetWidth() * film->GetHeight() * 3; ++i) {
        data[i] = i;
    }

    Renderer renderer(atoi(argv[2]));
    renderer.Init(*film);

    renderer.Render(scene);

    NetPBMLoader loader;
    loader.SavePPM(*film, "image");
    
    delete scene;

    return 0;
}
