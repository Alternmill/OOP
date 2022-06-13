#include "Grid.h"


Grid::Grid(int amount, float leftbot, float lefttop, float rightbot, float righttop)
{
	size = amount;
	gridIndices = new GLuint[4 * amount];
	gridVertices = new GLfloat[12 * amount];
	for (int i = 0; i < amount; i++) {
		gridVertices[i * 3 + 0] = leftbot;
		gridVertices[i * 3 + 1] = rightbot + i * (righttop - rightbot) / (amount - 1);
		gridVertices[i * 3 + 2] = 0;

		gridVertices[i * 3 + amount * 3 + 0] = lefttop;
		gridVertices[i * 3 + amount * 3 + 1] = rightbot + i * (righttop - rightbot) / (amount - 1);
		gridVertices[i * 3 + amount * 3 + 2] = 0;

		gridVertices[i * 3 + amount * 6 + 0] = leftbot + i * (lefttop - leftbot) / (amount - 1);
		gridVertices[i * 3 + amount * 6 + 1] = rightbot;
		gridVertices[i * 3 + amount * 6 + 2] = 0;

		gridVertices[i * 3 + amount * 9 + 0] = leftbot + i * (lefttop - leftbot) / (amount - 1);
		gridVertices[i * 3 + amount * 9 + 1] = righttop;
		gridVertices[i * 3 + amount * 9 + 2] = 0;

		gridIndices[i * 2] = i;
		gridIndices[i * 2 + 1] = i + amount*1;
		gridIndices[i * 2 + amount * 2] = i + amount * 2;
		gridIndices[i * 2 + 1 + amount * 2] = i + amount * 3;
	}
	GridVAO = new VAO();
	GridVAO->Bind();

	GridVBO = new VBO(gridVertices, sizeof(GLfloat)*12*amount);
	GridEBO = new EBO(gridIndices, sizeof(GLuint)*4*amount);
	GridVAO->LinkAttrib(*GridVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	GridVAO->Unbind();
	GridVBO->Unbind();
	GridEBO->Unbind();
}

void Grid::Draw(Shader& shader)
{
	GridVAO->Bind();
	glDrawElements(GL_LINES, size*4, GL_UNSIGNED_INT, 0);
}

Grid::~Grid()
{
	delete []gridIndices;
	delete []gridVertices;
	delete GridEBO;
	delete GridVBO;
	delete GridVAO;
}


