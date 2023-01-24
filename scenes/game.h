#ifndef GAME_H
#define GAME_H
#include <gf/Scene.h>
#include <gf/Math.h>
#include <gf/Time.h>
#include <gf/Action.h>
#include <gf/Views.h>
#include <gf/Widget.h>
#include <gf/WidgetContainer.h>
#include <gf/Coordinates.h>
#include <gf/Vector.h>
#include <gf/Color.h>
#include "../local/player.h"
#include "../local/level.h"
struct Manager;

class Game : public gf::Scene {
	private:
		gf::Action echapAction,spaceAction, mAction,rightAction,
		leftAction,upAction,downAction; 
		Manager& managerLink;
		Player player;
		Level level;
		gf::TextWidget m_score;
		gf::WidgetContainer m_widgets;
		


	public:
		Game(gf::Vector2i size, Manager& managerLink);
		Level& getLevel();
		void desactivateActions();
		void doHandleActions(gf::Window & window);
		void doUpdate(gf::Time time);
		void doRender (gf::RenderTarget &target, const gf::RenderStates &states) override;
		void init();
		void reset();
};

#endif
