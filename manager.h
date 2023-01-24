#ifndef MANAGER_H
#define MANAGER_H
#include "config.h"
#include <gf/GameManager.h>
#include "scenes/rules.h"
#include "scenes/title.h"
#include "scenes/end.h"
#include "scenes/game.h"
#include "scenes/pause.h"
constexpr gf::Vector2i WINDOW_SIZE = {800, 800};

class Manager : public gf::GameManager{
	public :
	Manager(std::string window_title);
	Title titleScene;
	Rules rulesScene;
	Pause pauseScene;
	End endScene;
	Game gameScene;
};





#endif
