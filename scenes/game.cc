#include "game.h"
#include <iostream>

#include "../manager.h"

Game::Game(gf::Vector2i size,Manager& link) :
	Scene(size),
	spaceAction("Press_space"),
	rightAction("Go right"),
	leftAction("Go left"),
	upAction("Go up"),
	downAction("Go down"),
	managerLink(link){

	
	setClearColor(gf::Color::Black);
	
	spaceAction.addKeycodeKeyControl(gf::Keycode::Space);
	addAction(spaceAction);


	rightAction.addKeycodeKeyControl(gf::Keycode::Right);
	rightAction.setInstantaneous();
	addAction(rightAction);

	leftAction.addKeycodeKeyControl(gf::Keycode::Left);
	leftAction.setInstantaneous();
	addAction(leftAction);

	player.setPosition({0,0});
	addWorldEntity(player);
	
}

void Game::doHandleActions(gf::Window & window){
	if(spaceAction.isActive()){
		managerLink.replaceScene(managerLink.endScene);
	}
	player.setVelocity({0,0});
	
	if(rightAction.isActive()){
		player.addVelocity({100,0});
	}
	if(leftAction.isActive()){
		player.addVelocity({-100,0});
	}
}
