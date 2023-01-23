#ifndef GAME_H
#define GAME_H
#include <gf/Scene.h>
#include <gf/Math.h>
#include <gf/Time.h>
#include <gf/Action.h>
#include <gf/Views.h>
#include <gf/Color.h>
#include "../local/player.h"
#include "../local/level.h"
struct Manager;

class Game : public gf::Scene {
	private:
		gf::Action rightAction,
		leftAction,upAction,downAction; 
		Manager& managerLink;
		Player player;
		Level level;
		


	public:
		Game(gf::Vector2i size, Manager& managerLink);
		Level& getLevel();
		void desactivateActions();
		void doHandleActions(gf::Window & window);
		void doUpdate(gf::Time time);
		void init();
		void reset();
		virtual void doShow();
};

#endif
