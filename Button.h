#ifndef BUTTON_CLASS_H
#define BUTTON_CLASS_H

#include"VAO.h"
#include"EBO.h"
#include"shaderClass.h"
class Button
{
private:
	float relx, rely;
	VBO* ButVBO;
	VAO* ButVAO;
	EBO* ButEBO;
	bool can_hold;
	bool is_clicked;
public:
	Button();
	Button(float relx, float rely);
	Button(float relx, float rely, bool hold);
	Button(float relx, float rely, bool hold,float xsize, float ysize);
	//Button(float relx, float rely, bool hold,VBO* nVBO, EBO* nEBO, VAO* nVAO)
	void isClicked();
	void draw();
};


#endif 