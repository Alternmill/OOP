#include "Map.h"

Map::Map(GLFWwindow* window,int screen_height, int screen_width, float rel_pos_x, float rel_pos_y,float rel_width,float rel_height, int num_col, int num_row, Shader& shader_on, Shader& shader_off)
{
	this->window = window;
	this->num_col = num_col;
	this->num_row = num_row;
	this->rel_height = rel_height;
	this->rel_pos_x = rel_pos_x;
	this->rel_pos_y = rel_pos_y;
	this->rel_width = rel_width;
	this->screen_height = screen_height;
	this->screen_width = screen_width;
	world.resize(num_col);
	for (int i = 0; i < num_col; i++) {
		world[i].resize(num_row);
		for (int j = 0; j < num_row; j++) {
			world[i][j] =*(new Tile_plain(rel_pos_x+i * (2*rel_width/ num_col),
										rel_pos_y+ j * (2*rel_height/ num_row),
										(2*rel_width/ num_col),
										(2*rel_height/ num_row)));
		}
	}
	prevx = -1;
	prevy = -1;
	was_pressed = 0;
	left_was_pressed = 0;
	right_was_pressed = 0;
}

void Map::Draw()
{
	//on.Activate();
	for (int i = 0; i < num_col; i++) {
		for (int j = 0; j < num_row; j++) {
		world[i][j].draw();	
		}
	}
}

bool Map::isOn(int mousex,int mousey) {
	mousey = screen_height - mousey;
	if (mousex<(rel_pos_x + 1) * screen_width / 2 ||
		mousex>((rel_pos_x + 1) / 2 + rel_width) * screen_width ||
		mousey<(rel_pos_y + 1) * screen_height / 2 ||
		mousey>((rel_pos_y + 1) / 2 + rel_height) * screen_height) {
		return 0;
	}
	return 1;
}

void Map::update(int mousex,int mousey,Color &color)
{
	double mouseX = mousex;
	double mouseY = mousey;
	static int flag;
	float red = color.r, green = color.g, blue = color.b;
	//glfwGetCursorPos(window, &mouseX, &mouseY);
	mouseY = screen_height - mouseY;

	if (mouseX<(rel_pos_x + 1) * screen_width /2||
		mouseX>((rel_pos_x + 1)/2 + rel_width) * screen_width ||
		mouseY<(rel_pos_y + 1) * screen_height /2||
		mouseY>((rel_pos_y + 1)/2 + rel_height) * screen_height) {
		if (flag >= 2) {
			prevx = -1;
			prevy = -1;
			return;
		}
			
		flag++;
	}
	else {
		flag = 0;
	}

	int posx = (mouseX - ((rel_pos_x + 1)/2) * screen_width)/(rel_width*screen_width)*num_col;
	int posy = (mouseY - ((rel_pos_y + 1)/2) * screen_height)/(rel_height * screen_height)*num_row;
	
	posy = std::min(posy, num_row-1);
	posx = std::min(posx, num_col - 1);
	posy = std::max(posy, 0);
	posx = std::max(posx, 0);
	
	if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE && left_was_pressed==1) ||
		(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE && right_was_pressed==1)) {
		prevx = -1;
		prevy = -1;
	}

	if ((was_pressed)&&glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		for (int i = 0; i < num_col; i++) {
			for (int j = 0; j < num_row; j++) {
				world[i][j].setColor(0,0,0);
			}
		}
		was_pressed = 0;
	}
	left_was_pressed = 0;
	right_was_pressed = 0;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		left_was_pressed = 1;
		world[posx][posy].setColor(red, green, blue);
		if (prevx == -1 || prevy == -1) {
			prevx = posx;
			prevy = posy;
		}
		else {
			if (abs(prevx - posx) > 1 || abs(prevy - posy) > 1) {
				if (posx > prevx) {
					if (posy > prevy) {
						double koef =(double) (posx - prevx + 1) / (posy - prevy + 1);
						double d1 = 0 , d2 = 0;
						while (prevx < posx || prevy < posy) {
							if (d1 <= d2 * koef) {
								prevx++; d1++;
							}
							else {	
								prevy++; d2++;
							}
							if (prevx < 0 || prevy < 0 || prevx >= num_col || prevy >= num_row)break;
							world[prevx][prevy].setColor(red, green, blue);
						}
						prevx = posx;
						prevy = posy;
					}else
					if (posy == prevy) {
						for (int i = prevx; i <= posx; i++)world[i][posy].setColor(red, green, blue);
						prevx = posx;
						prevy = posy;
					}else
					if (posy < prevy) {
						double koef = (double)(posx - prevx + 1) / (prevy - posy + 1);
						double d1 = 0, d2 = 0;
						while (prevx < posx || prevy > posy) {
							if (d1 <= d2 * koef) {
								prevx++; d1++;
							}
							else {
								prevy--; d2++;
							}
							if (prevx < 0 || prevy < 0 || prevx >= num_col || prevy >= num_row)break;
							world[prevx][prevy].setColor(red, green, blue);
						}
						prevx = posx;
						prevy = posy;
					}
				}else
				if (posx == prevx) {
					if (posy > prevy) {
						for (int i = prevy; i <= posy; i++)world[posx][i].setColor(red, green, blue);
						prevx = posx;
						prevy = posy;
					}else
					if (posy < prevy) {
						for (int i = posy; i <= prevy; i++)world[posx][i].setColor(red, green, blue);
						prevx = posx;
						prevy = posy;
					}
				}else
				if (posx < prevx) {
					if (posy > prevy) {
						double koef = (double)(prevx - posx + 1) / (posy - prevy + 1);
						double d1 = 0, d2 = 0;
						while (prevx > posx || prevy < posy) {
							if (d1 <= d2 * koef) {
								prevx--; d1++;
							}
							else {
								prevy++; d2++;
							}
							if (prevx < 0 || prevy < 0 || prevx >= num_col || prevy >= num_row)break;
							world[prevx][prevy].setColor(red, green, blue);
						}
						prevx = posx;
						prevy = posy;
					}else
					if (posy == prevy) {
						for (int i = posx; i <= prevx; i++)world[i][posy].setColor(red, green, blue);
						prevx = posx;
						prevy = posy;
					}else
					if (posy < prevy) {
						double koef = (double)(prevx - posx + 1) / (prevy - posy + 1);
						double d1 = 0, d2 = 0;
						while (prevx > posx || prevy > posy) {
							if (d1 <= d2 * koef) {
								prevx--; d1++;
							}
							else {
								prevy--; d2++;
							}
							if (prevx < 0 || prevy < 0 || prevx >= num_col || prevy >= num_row)break;
							world[prevx][prevy].setColor(red, green, blue);
						}
						prevx = posx;
						prevy = posy;
					}
				}
			}
			
		}
		prevx = posx;
		prevy = posy;
		was_pressed = 1;
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		right_was_pressed = 1;
		world[posx][posy].setColor(0, 0, 0);
		if (prevx == -1 || prevy == -1) {
			prevx = posx;
			prevy = posy;
		}
		else {
			if (abs(prevx - posx) > 1 || abs(prevy - posy) > 1) {
				if (posx > prevx) {
					if (posy > prevy) {
						double koef = (double)(posx - prevx + 1) / (posy - prevy + 1);
						double d1 = 0, d2 = 0;
						while (prevx < posx || prevy < posy) {
							if (d1 <= d2 * koef) {
								prevx++; d1++;
							}
							else {
								prevy++; d2++;
							}
							if (prevx < 0 || prevy < 0 || prevx >= num_col || prevy >= num_row)break;
							world[prevx][prevy].setColor(0, 0, 0);
						}
						prevx = posx;
						prevy = posy;
					}
					else
						if (posy == prevy) {
							for (int i = prevx; i <= posx; i++)world[i][posy].setColor(0, 0, 0);
							prevx = posx;
							prevy = posy;
						}
						else
							if (posy < prevy) {
								double koef = (double)(posx - prevx + 1) / (prevy - posy + 1);
								double d1 = 0, d2 = 0;
								while (prevx < posx || prevy > posy) {
									if (d1 <= d2 * koef) {
										prevx++; d1++;
									}
									else {
										prevy--; d2++;
									}
									if (prevx < 0 || prevy < 0 || prevx >= num_col || prevy >= num_row)break;
									world[prevx][prevy].setColor(0, 0, 0);
								}
								prevx = posx;
								prevy = posy;
							}
				}
				else
					if (posx == prevx) {
						if (posy > prevy) {
							for (int i = prevy; i <= posy; i++)world[posx][i].setColor(0, 0, 0);
							prevx = posx;
							prevy = posy;
						}
						else
							if (posy < prevy) {
								for (int i = posy; i <= prevy; i++)world[posx][i].setColor(0, 0, 0);
								prevx = posx;
								prevy = posy;
							}
					}
					else
						if (posx < prevx) {
							if (posy > prevy) {
								double koef = (double)(prevx - posx + 1) / (posy - prevy + 1);
								double d1 = 0, d2 = 0;
								while (prevx > posx || prevy < posy) {
									if (d1 <= d2 * koef) {
										prevx--; d1++;
									}
									else {
										prevy++; d2++;
									}
									if (prevx < 0 || prevy < 0 || prevx >= num_col || prevy >= num_row)break;
									world[prevx][prevy].setColor(0, 0, 0);
								}
								prevx = posx;
								prevy = posy;
							}
							else
								if (posy == prevy) {
									for (int i = posx; i <= prevx; i++)world[i][posy].setColor(0, 0, 0);
									prevx = posx;
									prevy = posy;
								}
								else
									if (posy < prevy) {
										double koef = (double)(prevx - posx + 1) / (prevy - posy + 1);
										double d1 = 0, d2 = 0;
										while (prevx > posx || prevy > posy) {
											if (d1 <= d2 * koef) {
												prevx--; d1++;
											}
											else {
												prevy--; d2++;
											}
											if (prevx < 0 || prevy < 0 || prevx >= num_col || prevy >= num_row)break;
											world[prevx][prevy].setColor(0, 0, 0);
										}
										prevx = posx;
										prevy = posy;
									}
						}
			}

		}
		prevx = posx;
		prevy = posy;
		was_pressed = 1;
	}
	
}
