#include "Mesh.h"

#include <iostream>
#include <iterator>

const std::vector<float> Mesh::noData;

void Mesh::generateTerrain(int dimensions)
{
	size_t count = dimensions * dimensions;
	float center = float(dimensions - 1) / 2.0f;
	float* vertices = new float[count * 3];
	float* normals = new float[count * 3];
	//float* textureCoords = new float[count * 2];
	unsigned int* indices = new unsigned int[2 * 3 * (dimensions - 1) * (dimensions - 1)];
	size_t vertexPointer = 0;
	for (int i = 0; i < dimensions; ++i)
	{
		for (int j = 0; j < dimensions; ++j)
		{
			vertices[vertexPointer * 3] = (float)(j - center);
			vertices[vertexPointer * 3 + 1] = 0.0f;
			vertices[vertexPointer * 3 + 2] = (float)(i - center);

			normals[vertexPointer * 3]		= 0.0f;
			normals[vertexPointer * 3 + 1]	= 1.0f;
			normals[vertexPointer * 3 + 2]	= 0.0f;

			//textureCoords[vertexPointer * 2] = (float)j / ((float)dimensions - 1);
			//textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)dimensions - 1);

			//std::cout << vertices[vertexPointer*3] << ", " << vertices[vertexPointer*3 + 1] << ", " << vertices[vertexPointer*3 + 2] << "\n";

			++vertexPointer;
		}
	}

	size_t pointer = 0;
	for (int row = 0; row < dimensions - 1; ++row)
	{
		for (int col = 0; col < dimensions - 1; ++col)
		{
			unsigned int pos = (row * dimensions) + col;
			indices[pointer++] = pos;
			indices[pointer++] = pos + dimensions;
			indices[pointer++] = pos + dimensions + 1;

			indices[pointer++] = pos + dimensions + 1;
			indices[pointer++] = pos + 1;
			indices[pointer++] = pos;
			
		}
	}
	std::vector<float> vertexData(vertices, vertices + vertexPointer*3);
	std::vector<float> normalData(normals, normals + vertexPointer*3);
	std::vector<unsigned int> indexData(indices, indices + pointer);
	
	loadToVAO(vertexData, normalData, noData, indexData);

	delete[] vertices;
	delete[] normals;
	delete[] indices;
}

void Mesh::generateCube()
{
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};

	float texcoords[] = {
		  0.0f, 0.0f,
		  1.0f, 0.0f,
		  1.0f, 1.0f,
		  1.0f, 1.0f,
		  0.0f, 1.0f,
		  0.0f, 0.0f,
		  0.0f, 0.0f,
		  1.0f, 0.0f,
		  1.0f, 1.0f,
		  1.0f, 1.0f,
		  0.0f, 1.0f,
		  0.0f, 0.0f,
		  1.0f, 0.0f,
		  1.0f, 1.0f,
		  0.0f, 1.0f,
		  0.0f, 1.0f,
		  0.0f, 0.0f,
		  1.0f, 0.0f,
		  1.0f, 0.0f,
		  1.0f, 1.0f,
		  0.0f, 1.0f,
		  0.0f, 1.0f,
		  0.0f, 0.0f,
		  1.0f, 0.0f,
		  0.0f, 1.0f,
		  1.0f, 1.0f,
		  1.0f, 0.0f,
		  1.0f, 0.0f,
		  0.0f, 0.0f,
		  0.0f, 1.0f,
		  0.0f, 1.0f,
		  1.0f, 1.0f,
		  1.0f, 0.0f,
		  1.0f, 0.0f,
		  0.0f, 0.0f,
		  0.0f, 1.0f
	};

	unsigned int indices[] = {
		0,1,2,2,3,0,

	};

	std::vector<float> vertexData(std::begin(vertices),std::end(vertices));
	std::vector<float> textureData(std::begin(texcoords), std::end(texcoords));
	std::vector<unsigned int> indexData(std::begin(indices), std::end(indices));

	loadToVAO(vertexData,noData,textureData,indexData);
}

void Mesh::generatePlane()
{
	float vertices[] = {
		0.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,
		1.0f,0.0f,1.0f,
		1.0f,0.0f,0.0f,
	};
	std::vector<float> vertexData(std::begin(vertices), std::end(vertices));

	unsigned int indices[] = {
		0,1,2,
		2,3,0
	};

	std::vector<unsigned int> indexData(std::begin(indices), std::end(indices));
	loadToVAO(vertexData, noData, noData, indexData);
}

void Mesh::loadToVAO(const std::vector<float>& positions,
	const std::vector<float>& normals,
	const std::vector<float>& textureCoords,
	const std::vector<unsigned int>& indices
)
{
	if (positions.size() && indices.size())
	{
		glGenVertexArrays(1, &VAO_);
		glBindVertexArray(VAO_);
		
		bindIndicesBuffer(indices);

		storeDataInAttributeList(0, 3, positions);
		storeDataInAttributeList(1, 3, normals);
		storeDataInAttributeList(2, 2, textureCoords);

		glBindVertexArray(0);
	}
}

void Mesh::storeDataInAttributeList(GLuint index, GLuint size, const std::vector<float>& data)
{
	if (!data.size()) return;
	size_t data_length = data.size() * sizeof(data[0]);
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data_length, &data[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, 0, 0);

	int error = glGetError();
	if (error) std::cout << error << "\n";
}

void Mesh::bindIndicesBuffer(const std::vector<unsigned int>& indices)
{
	indexCount_ = indices.size();
	if (!indices.size()) return;
	size_t data_length = indexCount_ * sizeof(indices[0]);
	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data_length, &indices[0], GL_STATIC_DRAW);
}
