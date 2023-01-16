#include "level.h"
#include <iostream>
#include <fstream>
#include <string.h>


Level::Level( Player* player_ptr,std::string path){
	load(path);
    player = player_ptr;
    this->win=false;
    this->loose = false;

    this->background = gf::RectangleShape({width*WALL_SIZE[0], height*WALL_SIZE[1]});
    this->background.setColor(gf::Color::Black);
    this->background.setAnchor(gf::Anchor::TopLeft);
    this->background.setPosition({0,0});
    
	
}

void Level::load(std::string path){
	level_path = path;
	FILE* f = fopen(level_path.c_str(),"r");
	if (f == nullptr){
		exit(1);
		return;
	}

	
	height = 0;
	char line[128];

	while (fgets(line,128,f)){
		std::cout<< line<<std::endl;

		width = strlen(line)-1;
		height++;
	}

	std::cout << "width : " << width << std::endl;
	std::cout << "height : " << height << std::endl;
	
	rewind(f);


	//fill level with empty walls
    for(float i = 0; i<this->height;i++){
        this->map.push_back({});
        
        for(float j = 0; j<this->width;j++){
            gf::Vector2f pos = {j,i};
            pos = pos*WALL_SIZE;
            this->map[i].push_back(Wall(pos,WallType::EMPTY));
        }
    }

	char c;
	int row = 0;
	int col = 0;
	while(!feof(f)){
		c = getc(f);
		switch(c){
			case '\0':
				break;
			case '\n':
				row++;
				col = -1;
				break;
			case 's':
				setStart({col,row});
				break;
			case 'e':
				setEnd({col,row});
				break;
			case 'o':
				setObject({col,row});
				break;
			case 't':
				setStatue({col,row});
				break;
			case '#':
				addWall({col,row});
				break;
		}
		std::cout << c;
		col++;
	}
			
	fclose(f);
	std::cout << "FILE READ END" << std::endl; 

}

void Level::reset(){	
    this->player->reset();
    this->player->setPosition(this->start * WALL_SIZE);
    this->setObject(object);
    this->setStatue(statue);
    this->win=false;
    this->loose = false;
    for (auto guard : guards){
    	guard->reset();
    }
}

bool Level::isWin(){
    return this->win;
}
bool Level::isLoose(){
    return this->loose;
}

Guard * Level::addGuard(gf::Vector2i grid_pos,std::vector<RouteAction *> newRoute){
	Guard *newGuard = new Guard(grid_pos);
	newGuard->setRoute(newRoute);
	guards.push_back(newGuard);
	return newGuard;
}

bool Level::addWall(gf::Vector2i position){
	if(this->isFreeSpace(position)){
        this->map[position.y][position.x].setType(WallType::SOLID);
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
    if(this->map[position.y][position.x].getType() == WallType::EMPTY){
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
    for (auto guard : guards){
    	(*guard).update(dt);
    }
	this->player->moveX(dt);
    this->player->handleCollisionX(this->checkCollisions());
	this->player->moveY(dt);
    this->player->handleCollisionY(this->checkCollisions());
    this->checkTakeObject();
    this->checkStatue();
    if (!this->checkWin()){
    	this->checkLoose();
    }

}

bool Level::setEnd(gf::Vector2i pos){
	if(this->isFreeSpace(pos)){
		this->map[pos.x][pos.y].setType(WallType::END);
		this->end = pos;  
		return true;
	}
	return false;
}

bool Level::setStart(gf::Vector2i pos){
	if(this->isFreeSpace(pos)){
		this->start = pos;
		this->map[pos.x][pos.y].setType(WallType::START);
        
		return true;
	}
	return false;	
}

bool Level::setObject(gf::Vector2i pos){
	if(this->isFreeSpace(pos)){
		this->object = pos;
		this->map[pos.x][pos.y].setType(WallType::OBJECT);
		return true;
	}
	return false;	
}

bool Level::setStatue(gf::Vector2i pos){
	if(this->isFreeSpace(pos)){
		this->statue = pos;
		this->map[pos.x][pos.y].setType(WallType::STATUE);
		return true;
	}
	return false;	
}

void Level::render(gf::RenderTarget& target, bool isMinimap){
    target.draw(this->background);
    for(auto line : this->map){
        for(auto& item : line){
        	if(item.getType()!=WallType::EMPTY){
            	item.render(target);
        	}
        }
    }
    if(!isMinimap){
        for (auto& guard : guards){
            (*guard).render(target);
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
            if(this->map[i][j].getRect().intersects(*(player->getRect()),intersection)){
            	return &this->map[i][j];
            }
        }
    }
    return nullptr;
}
bool Level::checkWin(){
    Wall square_end = this->map[end[0]][end[1]];
    gf::Rect<int> rect_intersection;
   	gf::Rect<int> *  playerRect = player->getRect();

    if(this->player->stoleTheObject()==true && square_end.getRect().intersects(*playerRect,rect_intersection)==true){
        this->win=true;
        return true;
    }
    return false;
}

bool Level::checkLoose(){
    gf::Rect<int> rect_intersection;
	gf::Rect<int>* playerRect = player->getRect();
    if(this->player->isAStatueBool()==false){
        for (auto& guard : guards){

            if(playerRect->intersects(*guard->getRect(),rect_intersection)){
                this->loose = true;
                return true;
            }
        }
    }
	return false;
}


void Level::checkTakeObject(){
    Wall square_object = this->map[object[0]][object[1]];
    gf::Rect<int> rect_intersection;
    if(square_object.getRect().intersects(*(this->player->getRect()),rect_intersection)==true){
        this->player->findObject();
        this->map[object[0]][object[1]].setType(WallType::EMPTY);
    }
}

void Level::checkStatue(){
    Wall square_statue = this->map[statue[0]][statue[1]];
    gf::Rect<int> rect_intersection;
    
    if(square_statue.getRect().intersects(*(this->player->getRect()),rect_intersection)==true){
        this->player->isAStatue();
        
        
    }

}



