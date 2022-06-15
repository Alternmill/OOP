#ifndef MAP_CLASS_H
#define MAP_CLASS_H

#include "Tile_plain.h"
#include<GLFW/glfw3.h>
#include<vector>	
#include <stdlib.h> 
#include "InterfaceElement.h"
#include "Color.h"
class Map : public InterfaceElement
{
private:
	std::vector<std::vector<Tile_plain>> world;
	Shader on, off;
	int prevx, prevy;
	bool was_pressed;
	bool left_was_pressed;
	bool right_was_pressed;
	int screen_height, screen_width;
	int num_col, num_row;
	float rel_pos_x, rel_pos_y,rel_height,rel_width;
	GLFWwindow* window;
public:
	Map(GLFWwindow* window,int screen_height, int screen_width, float rel_pos_x, float rel_pos_y,  float rel_width,float rel_height, int num_col, int num_row,Shader &shader_on,Shader &shader_off);
	void Draw()override;
	//void Update(GLFWwindow *window,float red,float green,float blue);
	bool isOn(int mousex, int mousey) override;
	void update(int mousex, int mousey, Color &color) override;
};

#endif // !MAP_CLASS_H

