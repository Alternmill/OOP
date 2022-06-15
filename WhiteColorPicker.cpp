#include "WhiteColorPicker.h"


void WhiteColorPicker::setWhite(Color col)
{
	float red = col.r; float green = col.g; float blue = col.b;
	float lred = 1.0 - red;
	float lgreen = 1.0 - green;
	float lblue = 1.0 - blue;
	lred /= (num_col - 1);
	lgreen /= (num_col - 1);
	lblue /= (num_col - 1);
	for (int i = 0; i < num_col; i++) {
		world[i][0].setColor(red, green, blue);
		red += lred;
		green += lgreen;
		blue += lblue;
	}
	Color res(
		world[lastx][lasty].getRed(),
		world[lastx][lasty].getGreen(),
		world[lastx][lasty].getBlue());
	curColor = res;
}

