#include <Mesh.h>
#include <iostream>
#include <fstream>
#include <sstream>

Mesh::Mesh() { }
Mesh::~Mesh() { }

void Mesh::LoadMesh(const std::string& filepath){
    std::ifstream file(filepath);
    if(!file){
        std::cerr << "Invalid File Path!" << std::endl;
        return ;
    }

    std::vector<Math::Vector3f> positions;
    std::vector<Math::Vector2f> texCoords;
    std::vector<Math::Vector3f> normals;
    std::vector<Face> rawFaces; 

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") { 
            Math::Vector3f pos;
            iss >> pos.x >> pos.y >> pos.z;
            positions.push_back(pos);
        } 
        else if (prefix == "vt") {
            Math::Vector2f tex;
            iss >> tex.x >> tex.y;
            texCoords.push_back(tex);
        } 
        else if (prefix == "vn") {
            Math::Vector3f norm;
            iss >> norm.x >> norm.y >> norm.z;
            normals.push_back(norm);
        } 
        else if (prefix == "f") { 
            Face face;
            std::string vertex;
            
            while (iss >> vertex) { 
                std::istringstream vss(vertex);
                std::string indexStr;
                int indices[3] = { -1, -1, -1 };
                int i = 0;

                while (std::getline(vss, indexStr, '/') && i < 3) {
                    if (!indexStr.empty()){ 
                        indices[i] = std::stoi(indexStr) - 1;
                    }
                    i++;
                }
                face.index.push_back(indices[0]);
                face.uvIndex.push_back(indices[1]);
                face.nIndex.push_back(indices[2]);
            }

            rawFaces.push_back(face);
        }
    }

    file.close();

    for (const auto& face : rawFaces) {
        if (face.index.size() < 3){ 
            continue;
        }
        for (size_t i = 1; i + 1 < face.index.size(); i++) {
            Face triFace;
            triFace.index = {face.index[0], face.index[i], face.index[i + 1]};
            triFace.uvIndex = {face.uvIndex[0], face.uvIndex[i], face.uvIndex[i + 1]};
            triFace.nIndex = {face.nIndex[0], face.nIndex[i], face.nIndex[i + 1]};
            faces.push_back(triFace);

            for (int j = 0; j < 3; j++) {
                Vertex v;
                v.v = positions[triFace.index[j]];
                v.uv = (triFace.uvIndex[j] >= 0) ? texCoords[triFace.uvIndex[j]] : Math::Vector2f(0.0f, 0.0f);
                v.normal = (triFace.nIndex[j] >= 0) ? normals[triFace.nIndex[j]] : Math::Vector3f(0.0f, 0.0f, 0.0f);
                vertices.push_back(v);
            }
        }
    }
}