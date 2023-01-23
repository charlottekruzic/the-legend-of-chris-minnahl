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
	managerLink(link),
	level(player){

	
	setClearColor(gf::Color::Black);

	//SET ACTIONS
	
	spaceAction.addKeycodeKeyControl(gf::Keycode::Space);
	addAction(spaceAction);


	rightAction.addKeycodeKeyControl(gf::Keycode::Right);
	rightAction.setContinuous();
	addAction(rightAction);

	leftAction.addKeycodeKeyControl(gf::Keycode::Left);
	leftAction.setContinuous();
	addAction(leftAction);

	upAction.addKeycodeKeyControl(gf::Keycode::Up);
	upAction.setContinuous();
	addAction(upAction);

	downAction.addKeycodeKeyControl(gf::Keycode::Down);
	downAction.setContinuous();
	addAction(downAction);


	
	//INITIALIZE PLAYER
	player.setPosition({100,100});

	//INITIALIZE LEVEL
	level.load("levels/1.txt");

	//ADD ENTITIES TO THE WORLD
	addWorldEntity(level);
	addWorldEntity(player);

	init();	
	
}
void Game::init(){
	level.init();
}

void Game::reset(){
	desactivateActions();
}


void Game::doHandleActions(gf::Window & window){
	if(spaceAction.isActive()){
		managerLink.replaceScene(managerLink.endScene);
	}
	
	if(rightAction.isActive()){
		player.addVelocity({1,0});
	}
	if(leftAction.isActive()){
		player.addVelocity({-1,0});
	}
	if(upAction.isActive()){
		player.addVelocity({0,-1});
	}
	if(downAction.isActive()){
		player.addVelocity({0,1});
	}
	if(level.checkGameOver()){
		managerLink.replaceScene(managerLink.endScene);
	}
}

Level& Game::getLevel(){
	return level;
}

void Game::desactivateActions(){
	rightAction.setInstantaneous();
	leftAction.setInstantaneous();
	upAction.setInstantaneous();
	downAction.setInstantaneous();

	rightAction.reset();
	leftAction.reset();
	upAction.reset();
	downAction.reset();

	rightAction.setContinuous();
	leftAction.setContinuous();
	upAction.setContinuous();
	downAction.setContinuous();	
}

void Game::doShow(){
	level.init();
}

void Game::doUpdate(gf::Time time){
	setWorldViewCenter(player.getPosition());

}
