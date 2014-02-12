#include "sceneparser.h"

Scene* SceneParser::BuildScene() const {
    ifstream file(filename.c_str(), ios::in);

    if(!file) {
        cerr << "Failed to open scene file " << filename << endl;
        return NULL;
    }

    Scene *scene = new Scene();
    string line;

    cout << "Parsing scene " << filename << endl;

    if(file.is_open()) {
        while (file.good()) {
            getline(file, line);
            char token = line[0];

            if(token == '#') {
                continue;
            } else if(token == 'c') {
                LoadCamera(scene, line.c_str());
            } else if(token == 'o') {
                LoadObject(scene, line.c_str());
            }
        } 
    }

    cout << "Loaded scene with " << scene->Objects().size() << " objects ";
    cout << "and " << scene->Lights().size() << " lights" << endl;

    file.close();

    return scene;
}

void SceneParser::LoadCamera(Scene* scene, const char* line) const {
    Vec3 la;
    Vec3 p;
    Vec2 res;

    int r = sscanf(line, "camera p(%f, %f, %f) la(%f, %f, %f) res(%f, %f)\n", 
            &p.x, &p.y, &p.z, &la.x, &la.y, &la.z, &res.x, &res.y);
    if(r < 8) {
        cerr << "Error while parsing camera" << endl;
        return;
    }

    res.x = (int) res.x;
    res.y = (int) res.y;

    Camera *cam = new Camera(p, res);
    cam->LookAt(la);
    scene->SetCamera(cam);
}

void SceneParser::LoadObject(Scene* scene, const char* line) const {
    Color c;
    Color e;
    Vec3 p;
    char m;
    char o;

    int r = sscanf(line, "object:%c p(%f, %f, %f) e(%f, %f, %f) c(%f, %f, %f) material:%c\n", 
            &o, &p.x, &p.y, &p.z, &e.r, &e.g, &e.b, &c.r, &c.g, &c.b, &m);

    if(r < 11) {
        cerr << "Error while parsing object at line:" << endl;
        cerr << line << endl;
        return;
    }

    Object *obj;

    switch(o) {
        case 's': obj = new Sphere(p, c, e); break;   
        case 'p': obj = new Plane(p, c, e); break;
        default: 
            cerr << "Unrecognized object at line:" << endl; 
            cerr << line << endl;
            return;
    }

    switch(m) {
        case 'd': obj->material = E_DIFFUSE; break;
        case 's': obj->material = E_SPECULAR; break;
        case 'r': obj->material = E_REFRACT; break;
        default:
            cerr << "Unrecognized material at line:" << endl;
            cerr << line << endl;
            return;
    }

    scene->AddObject(obj);
}
