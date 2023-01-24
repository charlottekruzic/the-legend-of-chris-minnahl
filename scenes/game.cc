#include "game.h"
#include <iostream>

#include "../manager.h"

Game::Game(gf::Vector2i size,Manager& link) :
	Scene(size),
	echapAction("press echap"),
	spaceAction("press Space"),
	mAction("Open map"),
	rightAction("Go right"),
	leftAction("Go left"), 
	upAction("Go up"),
	downAction("Go down"),
	managerLink(link),
	level(player),
	m_score("0/0", managerLink.resources.getFont("font/arial.ttf"), 25){

	
	setClearColor(gf::Color::Black);

	//SET ACTIONS
	spaceAction.addKeycodeKeyControl(gf::Keycode::Space);
	spaceAction.setContinuous();
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

	echapAction.addKeycodeKeyControl(gf::Keycode::Escape);
	echapAction.setInstantaneous();
	addAction(echapAction);

	mAction.addKeycodeKeyControl(gf::Keycode::M);
	mAction.setInstantaneous();
	addAction(mAction);
	
	//INITIALIZE PLAYER
	player.setPosition({100,100});

	//INITIALIZE LEVEL
	level.load("data/TheLegendOfChrisMinnahl/levels/3.txt");

	//SCORE
	m_score.setDefaultTextColor(gf::Color::White);
    m_score.setSelectedTextColor(gf::Color::White);
    m_score.setAnchor(gf::Anchor::TopLeft);
	m_widgets.addWidget(m_score);

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
	level.reset();
}


void Game::doHandleActions(gf::Window & window){
	if(!isPaused()){
		player.setWantToStatue(spaceAction.isActive());
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
		if(echapAction.isActive()){
			managerLink.gameScene.pause();
			managerLink.pushScene(managerLink.pauseScene);
		}

		if(mAction.isActive()){ //&& player.hasMap()
			managerLink.gameScene.pause();
			managerLink.pushScene(managerLink.mapScene);
		}

		if(level.checkGameOver()){
			managerLink.endScene.setLose();
			managerLink.replaceScene(managerLink.endScene);

		}
		if(level.checkWin()){
			managerLink.endScene.setWin();
			managerLink.replaceScene(managerLink.endScene);

		}
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

void Game::doUpdate(gf::Time time){
	setWorldViewCenter(player.getPosition());
}

void Game::doRender (gf::RenderTarget &target, const gf::RenderStates &states){
	renderWorldEntities(target,states);
	target.setView(getHudView());

	gf::Coordinates coords(target);
	std::string text_score = std::to_string(level.getNumberStolenObjects()) + "/" + std::to_string(level.getNumberTotalObjects());
	m_score.setString(text_score);
	m_score.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
    m_score.setPosition(coords.getRelativePoint({0.05f, 0.05f}));
	target.draw(m_score);
}
