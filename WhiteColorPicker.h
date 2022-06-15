#ifndef WHITE_COLOR_PICKER_H
#define WHITE_COLOR_PICKER_H
#include "ColorPicker.h"


class WhiteColorPicker :public ColorPicker
{
public:
	void setWhite(Color col);
	using ColorPicker::ColorPicker;
};

#endif