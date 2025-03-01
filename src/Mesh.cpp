#include <Mesh.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

Mesh::Mesh() { }
Mesh::Mesh(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices) : 
    vertices(_vertices), indices(_indices){ }
Mesh::~Mesh() { }

void Mesh::LoadMesh(SDL_Renderer* renderer, const std::string& path){
    Assimp::Importer importer;

    // Load the mesh using Assimp
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || !scene->HasMeshes()) {
        std::cerr << "ERROR::MESH::LOAD::FILE_NOT_FOUND or NO_MESHES" << std::endl;
        return;
    }

    aiMesh* mesh = scene->mMeshes[0];  // Load the first mesh (for simplicity)

    // Process vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        vertex.v = Vector3f(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex.normal = Vector3f(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        if (mesh->mTextureCoords[0]) {
            vertex.uv = Vector2f(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        } else {
            vertex.uv = Vector2f(0.0f, 0.0f);  // No texture coordinates
        }
        vertices.push_back(vertex);
    }

    // Process faces (indices)
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Load textures (for simplicity, load the first texture if any)
    if (scene->HasMaterials()) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        aiString texturePath;
        if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS) {
            Texture texture;
            texture.loadTexture(renderer, texturePath.C_Str());
            textures.push_back(texture);
        }
    }
}

void Mesh::MVP(Matrix& mvp){
    for (auto& vertex : vertices) {
        vertex.v = (mvp * vertex.v.to_Vector4f(1.0f)).to_Vector3f();
    }
}