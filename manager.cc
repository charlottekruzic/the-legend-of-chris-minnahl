#include "manager.h"

constexpr gf::Vector2i WINDOW_SIZE = {800, 800};

Manager::Manager(std::string window_title) : GameManager(window_title,ressource_paths), titleScene(WINDOW_SIZE), rulesScene(WINDOW_SIZE){
	getWindow().setSize(WINDOW_SIZE);
	

	pushScene(titleScene);
	start();
}

void Manager::start(){
	run();
}

