#ifndef LOCAL_BUTTON_H
#define LOCAL_BUTTON_H
#include "panel.h"
#include <gf/Font.h>
#include <gf/Widgets.h>

class Button : public Panel{
	private:
		gf::TextButtonWidget button;

	public:
	Button();
	Button(std::string string);
	Button(std::string string, void * func);
	Button(std::string string, gf::v1::Vector2f position, float size_text, gf::Color4f background_color, gf::Font &font);
	int setFunction(void * func);
	void click();
	gf::TextButtonWidget getButton();
};


#endif
