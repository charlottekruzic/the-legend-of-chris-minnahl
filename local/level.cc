#include "level.h"
#include <iostream>

Level::Level(gf::Vector2f size, Player* player,gf::Vector2i start, gf::Vector2i end): width(size.x),height(size.y) , player(player){
    this->win=false; 
    for(float i = 0; i<this->height;i++){
        this->map.push_back({});
        
        for(float j = 0; j<this->width;j++){
            gf::Vector2f pos = {j,i};
            pos = pos*WALL_SIZE;
            this->map[i].push_back(Wall(pos,WallType::Empty));
        }
    }
    if(!this->setStart(start)){exit(1);}
    if(!this->setEnd(end)){exit(1);}
    this->player->setPosition(this->start * WALL_SIZE);
}

void Level::reset(){
    //printf("AVANT velocity x : %f",this->player->getVelocity()[0]);
    //printf("AVANT velocity y : %f",this->player->getVelocity()[1]);
    this->player->stop();
    //printf("APRES velocity x : %f",this->player->getVelocity()[0]);
    //printf("APRES velocity y : %f",this->player->getVelocity()[1]);
    this->player->setPosition(this->start * WALL_SIZE);
    this->win=false;;
}

bool Level::isWin(){
    return this->win;
}


bool Level::addWall(gf::Vector2i position){
	if(this->isFreeSpace(position)){
        this->map[position.y][position.x].setType(WallType::Solid);
		return true;
    }
    return false;
}

bool Level::isFreeSpace(gf::Vector2i position){
    if(position.y < 0 || position.y >= this->height){
        return false;
    }
    if(position.x < 0 || position.x >= this->width){
        return false;
    }
    if(this->map[position.y][position.x].getType() == WallType::Empty){
    	return true;
    }
    return false;
}


bool Level::removeWall(gf::Vector2i position){
    return false;
}

void Level::prettyPrint(){
    std::cout << "-----------------------------------------\n";
    for(auto line : this->map){
        for(auto item : line){
            if(item.isSolid()){
                std::cout << "X|";
            }else{
                std::cout << " |";
            }
        }
        std::cout << "\n";
    }
}

void Level::update(float dt){
	this->player->moveX(dt);
    this->player->handleCollisionX(this->checkCollisions());
	this->player->moveY(dt);
    this->player->handleCollisionY(this->checkCollisions());
    this->checkWin();
}

bool Level::setEnd(gf::Vector2i pos){
	if(this->isFreeSpace(pos)){
		this->map[pos.x][pos.y].setType(WallType::End);
		this->end = pos;  
		return true;
	}
	return false;
}

bool Level::setStart(gf::Vector2i pos){
	if(this->isFreeSpace(pos)){
		this->start = pos;
		this->map[pos.x][pos.y].setType(WallType::Start);
		return true;
	}
	return false;	
}

void Level::render(gf::RenderTarget& target){
    for(auto line : this->map){
        for(auto& item : line){
        	if(item.getType()!=WallType::Empty){
            	item.render(target);
        	}
        }
    }

}

Wall* Level::checkCollisions(){
    for(int i=0;i<this->map.size();i++){
        for(int j=0;j<this->map[i].size();j++){
            gf::Rect<int> intersection;
            
            if(!this->map[i][j].isSolid()){
                continue;
            }
            if(this->map[i][j].getRect().intersects(this->player->getRect(),intersection)){
            	return &this->map[i][j];
            }
        }
    }
    return nullptr;
}

void Level::checkWin(){
    Wall square_end = this->map[end[0]][end[1]];
    gf::Rect<int> rect_intersection;
    if(square_end.getRect().intersects(this->player->getRect(),rect_intersection)==true){
        this->win=true;
    }
}



