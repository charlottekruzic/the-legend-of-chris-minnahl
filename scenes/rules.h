#ifndef RULES_H
#define RULES_H

#include <iostream>
#include <fstream>
#include <string>

#include <gf/Color.h>
#include <gf/Text.h>
#include <gf/Widgets.h>
#include <gf/Scene.h>
#include <gf/Math.h>
#include <gf/Time.h>
#include <gf/Action.h>
#include <gf/Font.h>
#include <gf/Coordinates.h>
struct Manager;

class Rules : public gf::Scene {
	private:
		gf::Action spaceAction; 
		Manager& managerLink;
		gf::Text titleRules; 
    	gf::Text gameRules;
		gf::Font font = gf::Font("data/arial.ttf");
		gf::TextButtonWidget returnButton = gf::TextButtonWidget("Return", font, 20.0);

	
	public:
		Rules(gf::Vector2i size,Manager& link);
		void doHandleActions(gf::Window & window);
		void doUpdate (gf::Time time);
		void doRender (gf::RenderTarget &target, const gf::RenderStates &states);
	
};

#endif
