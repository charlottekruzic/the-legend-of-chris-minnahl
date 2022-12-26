#ifndef LOCAL_BUTTON_H
#define LOCAL_BUTTON_H
#include "panel.h"

class Button : public Panel{
	private:

	public:
	Button();
	Button(std::string string);
	Button(std::string string, void * func);
	setFunction(void * func);
	void click();
}


#endif
