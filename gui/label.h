#ifndef LOCAL_LABEL_H
#define LOCAL_LABEL_H
#include "panel.h"
#include "gf/Text.h"
#include "gf/Font.h"
class Label : public Panel{
	private:
	gf::Text text;
	gf::Font font;
	public:
	Label();
	Label(std::string string);
	void setText(std::string string);
	void setTextColor(gf::Color4f newColor);
	std::string getText()const;
	void render(gf::RenderTarget& target);

	
};



#endif
