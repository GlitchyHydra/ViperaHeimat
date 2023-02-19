#pragma once

#include <memory>

#include "Scene/Mesh/Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Renderer;

class GameObject
{
public :
	GameObject(const std::string& path);
	~GameObject();

	void ClearTextures() { textures.clear(); }

	//Setters
	void SetTranslation(glm::vec3 nTranslation);
	void SetScale(glm::vec3 nScale) { scale = nScale; }
	void SetRotation(glm::vec3 nRotation) { rotation = nRotation; }
	void SetModelTrans(Shader* shader) const;

	//Getters
	glm::vec3& GetTranslation()  { return translation; }
	glm::vec3& GetRotation()     { return rotation;    }
	glm::vec3& GetScale()        { return scale;       }
	glm::mat4& GetTransform() const  { return totalTrans; }
	const std::vector<Mesh>& GetMeshes() const { return meshes; }
	const std::vector<Texture*>& GetTextures() const { return textures; }

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType typeName);

	bool IsNeedToRender() { return bNeedToRender; }

private:
	void loadModel();
	void processNode(aiNode* node, const aiScene* scene);
	void processMesh(aiMesh* ai_Mesh, const aiScene* scene, Mesh& mesh);
	void InitTextures(const aiScene* scene, const std::string& Filename);

private:
	bool bNeedToRender = true;
	std::vector<Mesh> meshes;
	std::vector<Texture*> textures;
	const std::string& mFilePath;
	mutable glm::mat4 totalTrans;

	glm::vec3 translation{ 960.f, 540.f, 10.f };
	glm::vec3 rotation{ 0.0f, 0.0f, 0.0f };
	glm::vec3 scale{ 100.0f, 100.0f, 100.0f };
};