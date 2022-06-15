#ifndef COLOR_H
#define COLOR_H
struct Color {
	float r = 1, g = 1, b = 1;
	Color() {
		r = 1; g = 1; b = 0;
	}
	Color(float red, float green, float blue) {
		r = red;
		g = green;
		b = blue;
	}
};
#endif // !COLOR_H
