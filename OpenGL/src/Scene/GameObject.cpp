#include "GameObject.h"

#include <iostream>

GameObject::~GameObject()
{
	
}


GameObject::GameObject(const std::string& path) :
    mFilePath(path)
{
    loadModel();
}

void GameObject::SetTranslation(glm::vec3 nTranslation)
{
    translation.x = nTranslation.x; 
    translation.y = nTranslation.y;
    translation.z = nTranslation.z;
}

void GameObject::loadModel()
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(mFilePath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }

    processNode(scene->mRootNode, scene);
}

void GameObject::processNode(aiNode* node, const aiScene* scene)
{
    // обработать все полигональные сетки в узле(если есть)
    meshes.reserve(scene->mNumMeshes);
    for (unsigned int i = 0; i < scene->mNumMeshes; i++)
    {
        meshes.emplace_back();
        processMesh(scene->mMeshes[i], scene, meshes[i]);
    }
    
    textures.resize(scene->mNumMaterials);
    InitTextures(scene, mFilePath);
}

void GameObject::processMesh(aiMesh* ai_Mesh, const aiScene* scene, Mesh& mesh)
{
    mesh.matInd = ai_Mesh->mMaterialIndex;
    //verticies
    for (unsigned int i = 0; i < ai_Mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vectorPosition(ai_Mesh->mVertices[i].x,
            ai_Mesh->mVertices[i].y, ai_Mesh->mVertices[i].z);

        glm::vec3 vectorNormal { 0.0f, 0.0f, 0.0f };
        if (ai_Mesh->mNormals != nullptr)
        {
            vectorNormal.x = ai_Mesh->mNormals[i].x;
            vectorNormal.y = ai_Mesh->mNormals[i].y;
            vectorNormal.z = ai_Mesh->mNormals[i].z;
        }

        glm::vec2 texCoords(0.f, 0.f);
        if (ai_Mesh->mTextureCoords[0])
        {
            texCoords.x = ai_Mesh->mTextureCoords[0][i].x;
            texCoords.y = ai_Mesh->mTextureCoords[0][i].y;
        }

        mesh.vertices.push_back({vectorPosition, vectorNormal, texCoords});
    }

    //indicies
    for (unsigned int i = 0; i < ai_Mesh->mNumFaces; i++)
    {
        aiFace& face = ai_Mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            mesh.indices.push_back(face.mIndices[j]);
    }

    mesh.SetupMesh();
}

void GameObject::InitTextures(const aiScene* scene, const std::string& Filename)
{
    std::string::size_type SlashIndex = Filename.find_last_of("/");
    std::string Dir;

    if (SlashIndex == std::string::npos)
    {
        Dir = ".";
    }
    else if (SlashIndex == 0)
    {
        Dir = "/";
    }
    else {
        Dir = Filename.substr(0, SlashIndex);
    }

    for (unsigned int i = 0; i < scene->mNumMaterials; i++)
    {
        const aiMaterial* aiMat = scene->mMaterials[i];
        textures[i] = NULL;
        
        if (aiMat->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {

            aiString Path;
            //other parameters in Func GetTexture is NULL
            bool getRes = aiMat->GetTexture(aiTextureType_DIFFUSE, 0, &Path);
            if (getRes == AI_SUCCESS)
            {
                //textures.emplace_back();
                std::string FullPath = Dir + "/" + Path.data;
                textures[i] = new Texture(FullPath.c_str(), i, TextureType::DIFFUSE );
                //textures[i]->Bind();
            }
        }
    }
}

void GameObject::SetModelTrans(Shader* shader) const
{
    totalTrans = glm::scale(glm::translate(glm::mat4(1.0f), translation), scale);
    totalTrans = glm::rotate(totalTrans, glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
    totalTrans = glm::rotate(totalTrans, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
    totalTrans = glm::rotate(totalTrans, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));
    
	shader->SetUniformMat4f("u_trans", totalTrans);
}

std::vector<Texture> GameObject::loadMaterialTextures(aiMaterial* mat, aiTextureType aiType, TextureType typeName)
{
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(aiType); i++)
    {
        aiString str;
        mat->GetTexture(aiType, i, &str);
        std::cout << "texture: " << str.C_Str() << std::endl;
        textures.push_back(Texture(str.C_Str(), i % 33));
    }

    return textures;
}
