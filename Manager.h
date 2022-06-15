#pragma once

#include<vector>
#include"InterfaceElement.h"
#include"Color.h"
#include<iostream>
class Manager
{
private:
	InterfaceElement* drawing_board;
	InterfaceElement* color_picker;
	InterfaceElement* whiteness_picker;
	
protected:
	Manager(InterfaceElement* drawing_board, InterfaceElement* color_picker, InterfaceElement* whiteness_picker);
	static Manager* manager;
public:
	
	void update(int mousex, int mousey, Color& color, Color& color1);
	void draw();
	InterfaceElement* get_drawing_board();
	InterfaceElement* get_color_picker();
	InterfaceElement* get_whiteness_picker();
	static Manager* GetInstance(InterfaceElement* drawing_board, InterfaceElement* color_picker, InterfaceElement* whiteness_picker);
	static Manager* GetInstance();
	
};

