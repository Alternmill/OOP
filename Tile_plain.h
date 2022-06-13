#ifndef ITILE_CLASS_H
#define ITILE_CLASS_H

#include "VAO.h"
#include "EBO.h"
#include "shaderClass.h"
class Tile_plain
{
private:
	double xpos, ypos;
	double xsize, ysize;
	GLfloat vertices[4 * 6];
	GLuint indices[6];
	VBO* TileVBO;
	EBO* TileEBO;
	VAO* TileVAO;
public:
	Tile_plain(double xPos, double yPos, double xSize, double ySize);
	Tile_plain();
	void draw();
	void setColor(float red,float green,float blue);
	float getRed();
	float getGreen();
	float getBlue();
};
#endif
