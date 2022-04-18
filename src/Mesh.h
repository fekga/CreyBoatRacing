#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

#include <vector>


class Mesh
{
	static const std::vector<float> noData;
public:
	void generateTerrain(int dimensions);

	void generateCube();

	void generatePlane();

	void loadToVAO(
		const std::vector<float>& positions, 
		const std::vector<float>& textureCoords,
		const std::vector<float>& normals,
		const std::vector<unsigned int>& indices
	);

	void storeDataInAttributeList(GLuint index, GLuint size, const std::vector<float>& data);

	void bindIndicesBuffer(const std::vector<unsigned int>& indices);

	void render()
	{
		glBindVertexArray(VAO_);
		glDrawElements(GL_TRIANGLES, indexCount_, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	GLuint VAO_ = 0;
	GLsizei indexCount_ = 0;
};

