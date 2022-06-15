#ifndef COLOR_PICKER_CLASS_H
#define COLOR_PICKER_CLASS_H

#include"Grid.h"
#include <vector>
#include <algorithm>
#include"Tile_plain.h"
#include<GLFW/glfw3.h>
#include "InterfaceElement.h"
#include "Color.h"


class ColorPicker : public InterfaceElement
{
protected:
	int prevx, prevy;
	bool was_pressed;
	bool left_was_pressed;
	bool right_was_pressed;
	int screen_height, screen_width;
	int num_col, num_row;
	int lastx, lasty;
	float rel_pos_x, rel_pos_y, rel_height, rel_width;
	Grid* grid;
	Color curColor;
	Shader* ColorShader;
	std::vector<std::vector<Tile_plain>> world;
	GLFWwindow* window;
public:
	ColorPicker(GLFWwindow* window,int screen_height, int screen_width,
				float rel_pos_x, float rel_pos_y,
				float rel_width, float rel_height,
				int num_col, int num_row,
				const char* vertexFile, const char* fragmentFile);

	void Draw()override;
	void setRainbow();
	Color getColor();
	bool isOn(int mousex, int mousey) override;
	void update(int mousex, int mousey, Color& color) override;
};

#endif

