#ifndef GAME_H
#define GAME_H
#include <gf/Scene.h>
#include <gf/Math.h>
#include <gf/Time.h>
#include <gf/Action.h>
#include <gf/Views.h>
#include <gf/Color.h>
#include "../local/player.h"
struct Manager;

class Game : public gf::Scene {
	private:
	gf::Action spaceAction,rightAction,
		leftAction,upAction,downAction; 
	Manager& managerLink;
	Player player;


	public:
	Game(gf::Vector2i size, Manager& managerLink);
	void doHandleActions(gf::Window & window);
};

#endif
