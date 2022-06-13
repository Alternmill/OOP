#ifndef COLOR_PICKER_CLASS_H
#define COLOR_PICKER_CLASS_H

#include"Grid.h"
#include <vector>
#include <algorithm>
#include"Tile_plain.h"
#include<GLFW/glfw3.h>


struct Color {
	float r = 1, g = 1, b = 1;
	Color() {
		r = 1; g = 1; b = 0;
	}
	Color(float red,float green, float blue) {
		r = red;
		g = green;
		b = blue;
	}
};

class ColorPicker
{
private:
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
public:
	ColorPicker(int screen_height, int screen_width,
				float rel_pos_x, float rel_pos_y,
				float rel_width, float rel_height,
				int num_col, int num_row,
				const char* vertexFile, const char* fragmentFile);

	void Draw();
	void setRainbow();
	Color getColor(GLFWwindow *window);
	void setWhite(Color col);

};

#endif

