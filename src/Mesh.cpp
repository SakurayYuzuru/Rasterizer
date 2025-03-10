#include <Mesh.h>
#include <iostream>
#include <fstream>
#include <sstream>

Mesh::Mesh() { }
Mesh::~Mesh() { }

bool Mesh::LoadMesh(const std::string& filepath){
    std::ifstream file(filepath);
    if(!file){
        std::cerr << "Invalid File Path!" << std::endl;
        return false;
    }

    std::vector<Math::Vector3f> positions;
    std::vector<Math::Vector2f> texCoords;
    std::vector<Math::Vector3f> normals;

    std::string line;
    while(std::getline(file, line)){
        std::istringstream iss(line);
        std::string flag;
        iss >> flag;

        if(flag == "v"){
            Math::Vector3f pos;
            iss >> pos.x >> pos.y >> pos.z;
            positions.push_back(pos);
        }else if(flag == "vt"){
            Math::Vector2f tex;
            iss >> tex.x >> tex.y;
            texCoords.push_back(tex);
        }else if(flag == "vn"){
            Math::Vector3f norm;
            iss >> norm.x >> norm.y >> norm.z;
            normals.push_back(norm);
        }else if(flag == "f"){
            std::vector<Face> faceIndices;
            std::vector<Vertex> faceVertices;

            std::string vertex;
            while(iss >> vertex){
                std::istringstream vss(vertex);
                std::string indexStr;
                int indices[3] = {-1, -1, -1};
                int i = 0;
                while(std::getline(vss, indexStr, '/') && i < 3){
                    if(!indexStr.empty()){
                        indices[i] = std::stoi(indexStr) - 1;
                    }
                    i ++;
                }

                Face face = {indices[0], indices[1], indices[2]};
                faceIndices.push_back(face);

                Vertex vertexData;
                vertexData.v = positions[indices[0]];
                if(indices[1] >= 0){
                    vertexData.uv = texCoords[indices[1]];
                }
                if(indices[2] >= 0){
                    vertexData.normal = normals[indices[2]];
                }
                faceVertices.push_back(vertexData);
                faceIndices.push_back({indices[0], indices[1], indices[2]});
            }

            for(int i = 1; i < faceVertices.size() - 1; ++ i){
                vertices.push_back(faceVertices[0]);
                vertices.push_back(faceVertices[i]);
                vertices.push_back(faceVertices[i + 1]);
                faces.push_back({faceIndices[0].index, faceIndices[i].uvIndex, faceIndices[i + 1].nIndex});
            }
        }
    }
    file.close();

    return true;
}