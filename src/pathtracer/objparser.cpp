#include "objparser.h"

void ObjParser::Parse(string objfile, Scene* scene, Vec3 pos, Vec3 col, Vec3 emis, MaterialType material) const {
    ifstream file(objfile.c_str(), ios::in); 
    if(!file) {
        cerr << "Can't open file " << objfile << endl;
        return;
    }

    int lines = 0; 
    while(file.ignore(std::numeric_limits<int>::max(), '\n')) { 
        ++lines; 
    } 
    file.close();

    ifstream f(objfile.c_str(), ios::in);

    cout << "Loading " << objfile << ".. " << endl;

    string token;
    vector<Vec3> vertices;
    int currentLine = 0;

    while(!f.eof()) {
        f >> token; 

        if(token == "#") {
            f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        } else if(token == "v") {   // vertex
            Vec3 vertex;
            f >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        } else if(token == "vt") {  // tex coord
        } else if(token == "vn") {  // vertex normal
        } else if(token == "f") {   // face
            string faceLine;
            getline(f, faceLine);

            for(unsigned int i = 0; i < faceLine.length(); ++i) {
                if(faceLine[i] == '/') {
                    faceLine[i] = ' ';
                }
            }

            stringstream ss(faceLine);
            string faceToken;

            Vec3 faceVertex[3];
            for(int i = 0; i < 6; ++i) {
                ss >> faceToken;
                if(faceToken.find_first_not_of("\t\n ") != string::npos) {
                    if(i % 2 == 0) {
                        faceVertex[i/2] = vertices[atoi(faceToken.c_str()) - 1];
                    } else {
                        // normals
                    }
                }
            }
            Triangle* triangle = new Triangle(faceVertex[0], faceVertex[1], faceVertex[2], pos, col, emis);
            triangle->material = material;
            scene->AddObject(triangle);
        }
        currentLine++;
    }
    f.close();
}
