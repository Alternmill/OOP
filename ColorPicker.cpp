#include "ColorPicker.h"

float fr(float x) {
	if (x <= (1.0 / 3)) {
		return 2 * (1.0 / 3 - x) / (1.0 / 3);
	}
	if (x >= (2.0 / 3)) {
		return 2 * (x - 2.0 / 3) / (1.0 / 3);
	}
	return 0;
}

float fg(float x) {
	if (x <= (1.0 / 3)) {
		return 2*(x) / (1.0 / 3);
	}
	if (x <= (2.0 / 3)) {
		return 2 * ((2.0 / 3) - x) / (1.0 / 3);
	}
	return 0;
}
float fb(float x) {
	if (x <= (2.0 / 3) && x >= (1.0 / 3)) {
		return 2 * (x - (1.0 / 3)) / (1.0 / 3);
	}
	if (x >= (2.0 / 3)) {
		return 2 * (1.0 - x) / (1.0 / 3);
	}
	return 0;
}


ColorPicker::ColorPicker(GLFWwindow* window,int screen_height, int screen_width, float rel_pos_x, float rel_pos_y, float rel_width, float rel_height, int num_col, int num_row, const char* vertexFile, const char* fragmentFile)
{
	this->window = window;
	curColor.r = 1;
	curColor.g = 1;
	curColor.b = 1;
	this->num_col = num_col;
	this->num_row = num_row;
	this->rel_height = rel_height;
	this->rel_pos_x = rel_pos_x;
	this->rel_pos_y = rel_pos_y;
	this->rel_width = rel_width;
	this->screen_height = screen_height;
	this->screen_width = screen_width;
	ColorShader = new Shader("default.vert", "default.frag");

	world.resize(num_col);
	for (int i = 0; i < num_col; i++) {
		world[i].resize(num_row);
		for (int j = 0; j < num_row; j++) {
			world[i][j] = *(new Tile_plain(rel_pos_x + i * (2 * rel_width / num_col),
				rel_pos_y + j * (2 * rel_height / num_row),
				(2 * rel_width / num_col),
				(2 * rel_height / num_row)));
			float k = (float)i / num_col;
			world[i][j].setColor(
				std::min(fr(k), 1.0f) * (float)(num_row - j) / num_row,
				std::min(fg(k), 1.0f) * (float)(num_row - j) / num_row,
				std::min(fb(k), 1.0f) * (float)(num_row - j) / num_row);
			
		}
	}
	setRainbow();
}

void ColorPicker::Draw()
{
	ColorShader->Activate();
	for (int i = 0; i < num_col; i++) {
		for (int j = 0; j < num_row; j++) {
			world[i][j].draw();
		}
	}
}

void ColorPicker::setRainbow()
{
	for (int i = 0; i < num_col; i++) {
		for (int j = 0; j < num_row; j++){
			float k = (float)i / num_col;
			world[i][j].setColor(
				std::min(fr(k), 1.0f) * (float)(num_row - j) / num_row,
				std::min(fg(k), 1.0f) * (float)(num_row - j) / num_row,
				std::min(fb(k), 1.0f) * (float)(num_row - j) / num_row);

		}
	}
}

bool ColorPicker::isOn(int mousex, int mousey) {
	mousey = screen_height - mousey;
	if (mousex<(rel_pos_x + 1) * screen_width / 2 ||
		mousex>((rel_pos_x + 1) / 2 + rel_width) * screen_width ||
		mousey<(rel_pos_y + 1) * screen_height / 2 ||
		mousey>((rel_pos_y + 1) / 2 + rel_height) * screen_height) {
		return 0;
	}
	return 1;
}



Color ColorPicker::getColor()
{
	return curColor;
}

void ColorPicker::update(int mousex,int mousey,Color &color) {

	double mouseX = mousex;
	double mouseY = mousey;
	//glfwGetCursorPos(window, &mouseX, &mouseY); 
	mouseY = screen_height - mouseY; 
	
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		
		color = curColor;
		return;
	}
	
	
	int posx = floor((float)(mouseX - ((rel_pos_x + 1) / 2) * screen_width) / (rel_width * screen_width) * (float)num_col);
	int posy = floor((float)(mouseY - ((rel_pos_y + 1) / 2) * screen_height) / (rel_height * screen_height) * (float)num_row);
	
	posy = std::min(posy, num_row - 1);
	posx = std::min(posx, num_col - 1);
	posy = std::max(posy, 0);
	posx = std::max(posx, 0);
	lastx = posx;
	lasty = posy;
	Color res(
		world[posx][posy].getRed(),
		world[posx][posy].getGreen(),
		world[posx][posy].getBlue());
	curColor = res;
	
	color = curColor;
}

