#ifndef GRID_CLASS_H
#define GRID_CLASS_H

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"

class Grid
{
private:
	GLfloat* gridVertices;
	GLuint* gridIndices;
	VAO* GridVAO;
	VBO* GridVBO;
	EBO* GridEBO;
	int size;
public:
	Grid(int amount, float leftbot, float lefttop,float rightbot, float righttop);
	void Draw(Shader &shader);
	~Grid();
};

#endif