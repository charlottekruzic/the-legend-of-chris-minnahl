#include "level.h"
#include <iostream>
Level::Level(Player & playerLink,Map & mapLink) : 
	map(mapLink),player(playerLink){
	reset();
}


void Level::reset(){
	std::cout << "reset guards" << std::endl;
	for (Guard & guard :map.getGuards()){
		guard.reset();
	}
	isGameOver = false;
	notFoundObjects = map.getObjects();	
	foundObjects = {}; 
	isWin = false;
	player.init();
	player.setPosition(map.getStart().getPosition());
	player.setVelocity({0,0});
	//only reset if level loaded at least once
}


void Level::addGuard(gf::Vector2i pos, std::vector<struct RouteAction > route){
	Guard newGuard = Guard(pos);
	newGuard.setRoute(route);
	guards.push_back(newGuard);
}

void Level::update(gf::Time time){
	for (Guard & guard :map.getGuards()){
		guard.update(time);
	}	

	//X MOTION
	player.applyXMotion(time);
	gf::RectF collider = findCollider();
	if(!collider.isEmpty()){
		if(player.getVelocity().x > 0){//RIGHT
			player.setPosition({collider.min.x-PLAYER_SIZE.x,player.getPosition().y });
		}else if(player.getVelocity().x < 0){
			player.setPosition({collider.max.x,player.getPosition().y});
		}
	}

	//Y MOTION
	player.applyYMotion(time);
	collider = findCollider();
	if(!collider.isEmpty()){
		if(player.getVelocity().y > 0){//DOWN
			player.setPosition({player.getPosition().x,collider.min.y- PLAYER_SIZE.y});
		}else if (player.getVelocity().y <0){
			player.setPosition({player.getPosition().x,collider.max.y });
		}
	}	
	player.setVelocity({0,0});
	if(!player.isAStatue() && checkGuards()){
		isGameOver = true;
	}
}

gf::RectF Level::findCollider(){
	int y = map.getHeight();
	int x = map.getWidth();

	//Level collision
	for(int row = 0 ; row < y; row++ ){
		for (int col = 0; col<x ; col++){
			gf::RectF tmp = testCollision(map.get(col,row));
			if(!tmp.isEmpty()){
				return tmp;
			}
		}
	}
	//Object collision
	std::vector<Wall> objList = notFoundObjects;
	for(Wall & obj:objList){
			gf::RectF tmp = testCollision(obj);
			if(!tmp.isEmpty()){
				return tmp;
			}	
	}
	//Statue collision
	std::vector<Wall> statueList = map.getStatues();
	for(Wall & statue:statueList){
			gf::RectF tmp = testCollision(statue);
			if(!tmp.isEmpty()){
				return tmp;
			}	
	}
	gf::RectF tmp = testCollision(map.getEnd());
	if(!tmp.isEmpty()){
		return tmp;
	}	
	tmp = testCollision(map.getStart());
	if(!tmp.isEmpty()){
		return tmp;
	}	
	return gf::RectF::empty();
}

gf::RectF Level::testCollision(Wall & wall){
	if(wall.getType() == WallType::EMPTY){return gf::RectF::empty();}
	gf::RectF wallRect = gf::RectF::fromPositionSize(wall.getPosition(),WALL_SIZE);
	gf::RectF playerRect = gf::RectF::fromPositionSize(player.getPosition(),PLAYER_SIZE);

	if(wallRect.intersects(playerRect)){
		//Custom collision code
		doWhenCollide(wall);
		if(wall.getType() == WallType::SOLID){
			return wallRect;
		}
		return gf::RectF::empty();
	}
	
	return	gf::RectF::empty();	
}

void Level::doWhenCollide(Wall & wall){
	//get grid position of the collided wall
	// int x = (int) wall.getPosition().x / WALL_SIZE.x;
	// int y = (int) wall.getPosition().y / WALL_SIZE.y;
	switch(wall.getType()){
		case WallType::OBJECT:
			foundObjects.push_back(wall);
			notFoundObjects.erase(
				std::remove_if(notFoundObjects.begin(), notFoundObjects.end(), 
					[wall](const Wall & other) {return wall.equals(other);}),
				notFoundObjects.end());
			break;
		case WallType::STATUE:
			if(player.isWantToStatue()){
				player.setStatue(true);
				player.setPosition(wall.getPosition());
			}else{
				player.setStatue(false);
			}
			break;
		case WallType::START:
			break;
		case WallType::END:
			if(notFoundObjects.size()==0){
				isWin = true;
			}
			break;
		default:
			break;	
	}
}
bool Level::checkGuards(){
	gf::RectF playerRect = gf::RectF::fromPositionSize(player.getPosition(),PLAYER_SIZE);
	for(Guard & guard : map.getGuards()){
		gf::RectF guardRect = *guard.getRect();
		if(guardRect.intersects(playerRect)){
			return true;
		}
	}
	return false;
}
void Level::render(gf::RenderTarget & target, const gf::RenderStates & states){
	int y = map.getHeight();
	int x = map.getWidth();
	for(int row = 0 ; row < y; row++ ){
		for (int col = 0; col<x ; col++){
			map.get(col,row).render(target);
		}
	}
	
	for(Wall & obj : notFoundObjects){
		obj.render(target);
	}
	
	std::vector<Wall> statuesList = map.getStatues();

	for(Wall & wall : statuesList){
		wall.render(target);
	}

	for(Guard & guard : map.getGuards()){
		guard.render(target);
	}
	
	map.getStart().render(target);
	map.getEnd().render(target);


}
bool Level::checkGameOver(){
	return isGameOver;
}

bool Level::checkWin(){
	return isWin;
}

std::vector<Wall> & Level::getFoundObjects(){
	return foundObjects;
}
std::vector<Wall> & Level::getNotFoundObjects(){
	return notFoundObjects;
}

