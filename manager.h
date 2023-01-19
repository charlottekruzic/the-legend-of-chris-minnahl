#ifndef MANAGER_H
#define MANAGER_H
#include <gf/GameManager.h>
#include "scenes/title.h"
#include "scenes/rules.h"


constexpr std::initializer_list<gf::Path> ressource_paths = {};

class Manager : public gf::GameManager{
	public :
	Manager(std::string window_title);
	Title titleScene;
	Rules rulesScene;


	void start();

};





#endif
