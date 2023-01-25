#ifndef MAP_H
#define MAP_H

#include <gf/Scene.h>
#include <gf/Action.h>
#include <gf/Coordinates.h>
#include <gf/Widgets.h>
#include <gf/WidgetContainer.h>

struct Manager;

class Map : public gf::Scene {
	private:
		Manager& m_managerLink;
        gf::Action m_mAction;
		gf::TextWidget m_closeMap;
		gf::TextButtonWidget m_buttonGame;
		gf::WidgetContainer m_widgets;

	
	public:
		Map(gf::Vector2i size,Manager& link);
        void doHandleActions(gf::Window & window) override;
		void doRender (gf::RenderTarget &target, const gf::RenderStates &states) override;
	
};

#endif