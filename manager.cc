#include "manager.h"



Manager::Manager(std::string window_title) : 
	GameManager(window_title,ressource_paths),
	gameScene(WINDOW_SIZE,*this),
	titleScene(WINDOW_SIZE,*this),
	rulesScene(WINDOW_SIZE,*this){
	getWindow().setSize(WINDOW_SIZE);
	

	pushScene(titleScene);
	run();
}

