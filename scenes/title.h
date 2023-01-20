#ifndef TITLE_H
#define TITLE_H
#include <gf/Scene.h>
#include <gf/Math.h>
#include <gf/Time.h>
#include <gf/Action.h>
#include <gf/Views.h>
#include <gf/Color.h>
#include <string>
#include <gf/Widgets.h>
#include <gf/Text.h>
#include <gf/Font.h>
#include <gf/Coordinates.h>

struct Manager;

class Title : public gf::Scene {
	private:
	gf::Action spaceAction; 
	Manager& managerLink;
	gf::Text titleMenu;
	gf::Font font = gf::Font("data/arial.ttf");
	std::vector<gf::TextButtonWidget> buttons;
	gf::TextButtonWidget button1 = gf::TextButtonWidget("Start", font, 30.0);
    gf::TextButtonWidget button2 = gf::TextButtonWidget("Rules", font, 30.0);
    gf::TextButtonWidget button3 = gf::TextButtonWidget("Exit", font,  30.0);
    

	public:
		Title(gf::Vector2i size, Manager& managerLink);
		void doHandleActions(gf::Window & window);
		void doUpdate (gf::Time time);
		void doRender (gf::RenderTarget &target, const gf::RenderStates &states);
	
};

#endif
