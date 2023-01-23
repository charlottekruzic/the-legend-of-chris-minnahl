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
#include <gf/WidgetContainer.h>
#include <gf/Text.h>
#include <gf/Font.h>
#include <gf/Coordinates.h>

struct Manager;

class Title : public gf::Scene {
	private: 
	Manager& managerLink;
	gf::Font font = gf::Font("data/arial.ttf");
	gf::WidgetContainer buttons;
	gf::TextButtonWidget buttonStart;
    gf::TextButtonWidget buttonRules; 
    gf::TextButtonWidget buttonQuit;
    

	public:
		Title(gf::Vector2i size, Manager& managerLink);
		 void doProcessEvent(gf::Event& event) override;
		void doUpdate (gf::Time time);
		void doRender(gf::RenderTarget& target, const gf::RenderStates &states) override;
		void doShow() override;
	
};

#endif
