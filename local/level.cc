#include "level.h"
#include <iostream>

Level::Level(gf::Vector2f size){
    this->width = size.x;
    this->height = size.y;
    for(float i = 0; i<this->height;i++){
        this->map.push_back({});
        for(float j = 0; j<this->width;j++){
            gf::Vector2f pos = {j,i};
            pos = pos*WALL_SIZE;
            this->map[i].push_back(Wall(pos,WallType::Empty));
        }
    }
}

bool Level::addWall(gf::Vector2i position){
    if(position.y < 0 || position.y >= this->height){
        return false;
    }
    if(position.x < 0 || position.x >= this->width){
        return false;
    }

    if(!this->map[position.y][position.x].isSolid()){
        this->map[position.y][position.x].setType(WallType::Solid);
    }
    return true;
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
}

void Level::render(gf::RenderTarget& target){
    for(auto line : this->map){
        for(auto& item : line){
        	if(item.isSolid()){
            	item.render(target);
        	}
        }
    }
}
