#include "manager.h"


constexpr gf::Vector2i WINDOW_SIZE = {800, 800};

Manager::Manager(std::string window_title) : 
	GameManager(window_title,ressource_paths),
	titleScene(WINDOW_SIZE,*this), rulesScene(WINDOW_SIZE,*this){
	getWindow().setSize(WINDOW_SIZE);
	

	pushScene(titleScene);
	run();
}

