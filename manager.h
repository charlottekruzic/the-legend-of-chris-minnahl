#ifndef MANAGER_H
#define MANAGER_H
#include <gf/GameManager.h>
#include "scenes/rules.h"
#include "scenes/title.h"
#include "scenes/game.h"
constexpr gf::Vector2i WINDOW_SIZE = {800, 800};

constexpr std::initializer_list<gf::Path> ressource_paths = {};

class Manager : public gf::GameManager{
	public :
	Manager(std::string window_title);
	Title titleScene;
	Rules rulesScene;
	Game gameScene;

};





#endif
