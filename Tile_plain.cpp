#include "Tile_plain.h"

Tile_plain::Tile_plain(double xPos, double yPos, double xSize, double ySize) {
	xpos = xPos;
	ypos = yPos;
	xsize = xSize;
	ysize = ySize;
	//bt-lt
	vertices[0] = xPos;
	vertices[1] = yPos;
	vertices[2] = 0;

	vertices[3] = 0;
	vertices[4] = 0;
	vertices[5] = 0;
	//tp-lt
	vertices[6] = xPos;
	vertices[7] = yPos + ySize;
	vertices[8] = 0;

	vertices[9] = 0;
	vertices[10] = 0;
	vertices[11] = 0;
	//bt-rt
	vertices[12] = xPos + xSize;
	vertices[13] = yPos;
	vertices[14] = 0;

	vertices[15] = 0;
	vertices[16] = 0;
	vertices[17] = 0;
	//tp-rt
	vertices[18] = xPos + xSize;
	vertices[19] = yPos + ySize;
	vertices[20] = 0;

	vertices[21] = 0;
	vertices[22] = 0;
	vertices[23] = 0;


	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 1;
	indices[4] = 2;
	indices[5] = 3;

	TileVAO = new VAO();
	TileVAO->Bind();

	TileVBO = new VBO(vertices, sizeof(GLfloat) * 24);
	
	TileEBO = new EBO(indices, sizeof(GLuint) * 6);


	TileVAO->LinkAttrib(*TileVBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	TileVAO->LinkAttrib(*TileVBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	TileVAO->Unbind();
	TileEBO->Unbind();
	TileVBO->Unbind();
}

Tile_plain::Tile_plain()
{
}


void Tile_plain::draw()
{
	TileVAO->Bind();




	glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT, 0);
}

void Tile_plain::setColor(float red,float green,float blue)
{
	vertices[3] = red;
	vertices[4] = green;
	vertices[5] = blue;

	vertices[9] = red;
	vertices[10] = green;
	vertices[11] = blue;

	vertices[15] = red;
	vertices[16] = green;
	vertices[17] = blue;

	vertices[21] = red;
	vertices[22] = green;
	vertices[23] = blue;

	TileVAO->Delete();
	TileVBO->Delete();
	delete TileVAO;
	delete TileVBO;
	TileVAO = new VAO();
	TileVAO->Bind();
	TileEBO->Bind();

	TileVBO = new VBO(vertices, sizeof(GLfloat) * 24);

	TileVAO->LinkAttrib(*TileVBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	TileVAO->LinkAttrib(*TileVBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	TileVAO->Unbind();
	TileEBO->Unbind();
	TileVBO->Unbind();
}

float Tile_plain::getRed()
{
	return vertices[3];
}

float Tile_plain::getGreen()
{
	return vertices[4];
}

float Tile_plain::getBlue()
{
	return vertices[5];
}
