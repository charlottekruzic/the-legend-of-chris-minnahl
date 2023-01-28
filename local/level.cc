#include "level.h"
#include <iostream>
Level::Level(Player & playerLink,Map & mapLink, gf::ResourceManager & resources) 
: map(mapLink)
, player(playerLink)
, m_resources(resources)
, m_wall_texture(m_resources.getTexture(m_resources.getAbsolutePath("sprites/wall/wall.png")))
, m_object_not_found_texture(m_resources.getTexture(m_resources.getAbsolutePath("sprites/wall/object_not_found.png")))
//, m_object_found_texture(m_resources.getTexture(m_resources.getAbsolutePath("sprites/wall/object_found.png")))
, m_floor_texture(m_resources.getTexture(m_resources.getAbsolutePath("sprites/wall/floor.png")))
, m_statue_texture(m_resources.getTexture(m_resources.getAbsolutePath("sprites/wall/socle_statue.png")))
, m_start_texture(m_resources.getTexture(m_resources.getAbsolutePath("sprites/wall/start.png")))
, m_end_texture(m_resources.getTexture(m_resources.getAbsolutePath("sprites/wall/end.png")))
, m_guard_textureRight(m_resources.getTexture(m_resources.getAbsolutePath("sprites/guard/tile020.png")))
, m_guard_textureLeft(m_resources.getTexture(m_resources.getAbsolutePath("sprites/guard/tile010.png")))
, m_guard_textureDown(m_resources.getTexture(m_resources.getAbsolutePath("sprites/guard/tile011.png")))
, m_guard_textureUp(m_resources.getTexture(m_resources.getAbsolutePath("sprites/guard/tile009.png")))
{

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
	
	bool find = false;
	
	//render wall
	int y = map.getHeight();
	int x = map.getWidth();
	for(int row = 0 ; row < y; row++ ){
		for (int col = 0; col<x ; col++){
			find = false;
			Wall wall = map.get(col,row);
			WallType type = wall.getType();
			gf::Vector2f sprite_position = {wall.getPosition().x, wall.getPosition().y+WALL_SIZE.y};

			//ground
			if(wall.getType()==WallType::EMPTY){
				m_floor_sprite.setAnchor(gf::Anchor::BottomLeft);
				m_floor_sprite.setPosition(sprite_position);
				m_floor_sprite.setTexture(m_floor_texture);
				target.draw(m_floor_sprite);
			}

			//object not found
			for(Wall & obj : notFoundObjects){
				if(obj.getPosition()==wall.getPosition()){
					m_object_not_found_sprite.setAnchor(gf::Anchor::BottomLeft);
					m_object_not_found_sprite.setPosition(sprite_position);
					m_object_not_found_sprite.setTexture(m_object_not_found_texture);
					m_object_not_found_sprite.setScale(1);
					target.draw(m_object_not_found_sprite);
					find=true;
				}
			}

			//statue
			if(!find){
				std::vector<Wall> statuesList = map.getStatues();
				for(Wall & statue : statuesList){
					if(statue.getPosition()==wall.getPosition()){
						m_statue_sprite.setAnchor(gf::Anchor::BottomLeft);
						m_statue_sprite.setPosition(sprite_position);
						m_statue_sprite.setTexture(m_statue_texture);
						m_statue_sprite.setScale(1);
						target.draw(m_statue_sprite);
						find=true;
					}
				}

			};


			//start
			if(!find){
				if(map.getStart().getPosition()==wall.getPosition()){
					m_start_sprite.setAnchor(gf::Anchor::BottomLeft);
					m_start_sprite.setPosition(sprite_position);
					m_start_sprite.setTexture(m_start_texture);
					m_start_sprite.setScale(1);
					target.draw(m_start_sprite);
					find=true;
				}				
			};




			//end
			if(!find){
				if(map.getEnd().getPosition()==wall.getPosition()){
					m_end_sprite.setAnchor(gf::Anchor::BottomLeft);
					m_end_sprite.setPosition(sprite_position);
					m_end_sprite.setTexture(m_end_texture);
					m_end_sprite.setScale(1);
					target.draw(m_end_sprite);
					find=true;
				}				
			};

		

			//wall
			if(!find){
				if(wall.getType()==WallType::SOLID){
					m_wall_sprite.setAnchor(gf::Anchor::BottomLeft);
					m_wall_sprite.setPosition(sprite_position);
					m_wall_sprite.setTexture(m_wall_texture);
					target.draw(m_wall_sprite);
				}				
			};

			if(row == player.getGridPosY()){
				std::cout << player.getGridPosY() << std::endl;
				player.render(target,states);
			}

		}
	}

	for(Guard & guard : map.getGuards()){
		guard.render(target);
		gf::Vector2f sprite_position = {guard.getPosition().x, guard.getPosition().y+GUARD_SIZE.y};
		m_guard_sprite.setAnchor(gf::Anchor::BottomLeft);
		m_guard_sprite.setPosition(sprite_position);
		if(guard.getdirectionGuard()==1){
			m_guard_sprite.setTexture(m_guard_textureRight);
		}else if(guard.getdirectionGuard()==2){
			m_guard_sprite.setTexture(m_guard_textureLeft);
		}else if(guard.getdirectionGuard()==3){
			m_guard_sprite.setTexture(m_guard_textureDown);
		}else if(guard.getdirectionGuard()==4){
			m_guard_sprite.setTexture(m_guard_textureUp);
		}
		
		m_guard_sprite.setScale(0.8);
		target.draw(m_guard_sprite);
	}



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

