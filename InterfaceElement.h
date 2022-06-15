#ifndef INTERFACE_ELEMENT_H
#define INTERFACE_ELEMENT_H

#include "Color.h"
class InterfaceElement
{
public:
	bool virtual isOn(int mousex, int mousey) = 0;
	void virtual update(int mousex, int mousey, Color& color) = 0;
	void virtual Draw() = 0;
};

#endif // !INTERFACE_ELEMET_H