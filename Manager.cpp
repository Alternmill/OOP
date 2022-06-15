#include "Manager.h"

Manager* Manager::manager = nullptr;

void Manager::update(int mousex,int mousey,Color &color, Color &color1)
{
	
	if (drawing_board->isOn(mousex, mousey)) {
		drawing_board->update(mousex,mousey,color);
	}
	if (color_picker->isOn(mousex, mousey)) {
		color_picker->update(mousex, mousey, color1);
	}
	if (whiteness_picker->isOn(mousex, mousey)) {
		whiteness_picker->update(mousex, mousey, color);

	}
}

void Manager::draw()
{
	drawing_board->Draw();
	color_picker->Draw();
	whiteness_picker->Draw();
}

InterfaceElement* Manager::get_drawing_board()
{
	return drawing_board;
}

InterfaceElement* Manager::get_color_picker()
{
	return color_picker;
}

InterfaceElement* Manager::get_whiteness_picker()
{
	return whiteness_picker;
}

Manager* Manager::GetInstance(InterfaceElement* drawing_board, InterfaceElement* color_picker, InterfaceElement* whiteness_picker)
{
	if (Manager::manager == nullptr) {
		Manager::manager = new Manager(drawing_board, color_picker, whiteness_picker);
	}
	return Manager::manager;
	
}

Manager* Manager::GetInstance()
{
	if (Manager::manager == nullptr) {
		throw ("Manager has not been created yet, make sure to pass all parameters before using it");
	}
	return Manager::manager;
}

Manager::Manager(InterfaceElement* drawing_board, InterfaceElement* color_picker, InterfaceElement* whiteness_picker)
{
	this->drawing_board = drawing_board;
	this->color_picker = color_picker;
	this->whiteness_picker = whiteness_picker;
}


