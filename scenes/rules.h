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
#include <gf/WidgetContainer.h>


struct Manager;

class Rules : public gf::Scene {
	private:
		Manager& m_managerLink;
		gf::Text m_title; 
    	gf::Text m_rules;
		gf::Font m_font;
		gf::TextButtonWidget m_returnButton;
		gf::WidgetContainer m_widgets;

	
	public:
		Rules(gf::Vector2i size,Manager& link);
		void renderTitle(gf::RenderTarget &target);
		void renderButton(gf::RenderTarget &target);
		void renderRules(gf::RenderTarget &target);
		void doProcessEvent(gf::Event& event) override;
		void doRender (gf::RenderTarget &target, const gf::RenderStates &states) override;
	
};

#endif
