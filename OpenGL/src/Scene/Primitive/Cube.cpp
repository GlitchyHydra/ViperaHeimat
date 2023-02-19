#include "Cube.h"

#include <iostream>

void calcNormals(const unsigned int* pIndices, const unsigned int indexCount, Vertex* pVertices, unsigned int vertSize, Cube* cube)
{
	for (unsigned int i = 0; i < indexCount; i += 3) {
		unsigned int index0 = pIndices[i];
		unsigned int index1 = pIndices[i + 1];
		unsigned int index2 = pIndices[i + 2];
		glm::vec3 v1 = pVertices[index1].pos - pVertices[index0].pos;
		glm::vec3 v2 = pVertices[index2].pos - pVertices[index0].pos;
		glm::vec3 normal = cross(v1, v2);
		normal = normalize(normal);
		pVertices[index0].normal += normal;
		pVertices[index1].normal += normal;
		pVertices[index2].normal += normal;
	}

	for (unsigned int i = 0; i < vertSize; i++)
	{
		pVertices[i].normal = normalize(pVertices[i].normal);
	}
}

Cube::Cube()
{
	//calcNormals(indicesInfo, 36, vertexInfo, 8, this);
	va.Bind();
    ib.setupData((unsigned int*)&indicesInfo[0], sizeIndices);
	vb.setupData((float*)&vertexInfo[0], sizeof(float) * sizeVertex);
	layout.Push<float>(3);
	layout.Push<float>(2);
	layout.Push<float>(3);
	va.AddBuffer(vb, layout);
	va.Unbind();
}
