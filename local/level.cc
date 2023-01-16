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

		width = strlen(line)-1;
		height++;
	}

	
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
                this->numberTotalOfObject++;
				break;
			case 't':
				setStatue({col,row});
				break;
			case '#':
				addWall({col,row});
				break;
		}
		if(c=='\0'){break;}
		col++;
	}
			
	fclose(f);

}

gf::Vector2f Level::getSize(){
    return {this->width*WALL_SIZE[0], this->height*WALL_SIZE[1]};
}

float Level::getWidth(){
    return this->width*WALL_SIZE[0];
}

float Level::getHeight(){
    return this->height*WALL_SIZE[1];
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
		this->map[pos.y][pos.x].setType(WallType::END);
		this->end = pos;  
		return true;
	}
	return false;
}

bool Level::setStart(gf::Vector2i pos){
	if(this->isFreeSpace(pos)){
		this->start = pos;
		this->map[pos.y][pos.x].setType(WallType::START);
        
		return true;
	}
	return false;	
}

bool Level::setObject(gf::Vector2i pos){
	if(this->isFreeSpace(pos)){
		this->object = pos;
		this->map[pos.y][pos.x].setType(WallType::OBJECT);
		return true;
	}
	return false;	
}

bool Level::setStatue(gf::Vector2i pos){
	if(this->isFreeSpace(pos)){
		this->statue = pos;
		this->map[pos.y][pos.x].setType(WallType::STATUE);
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

void Level::renderScore(gf::RenderTarget& target, gf::Vector2f size){
    gf::Font font("arial.ttf");
    std::string text_score = std::to_string(this->player->NumberOfObjectsStolen()) + "/" + std::to_string(this->numberTotalOfObject);
    gf::Text score(text_score, font,25);
    score.setAnchor(gf::Anchor::TopLeft);
    score.setPosition({this->player->getPosition()[0]-size[0]/2, this->player->getPosition()[1]-size[1]/2});
    target.draw(score);
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
    Wall square_end = this->map[end[1]][end[0]];
    gf::Rect<int> rect_intersection;
   	gf::Rect<int> *  playerRect = player->getRect();

    if(this->player->NumberOfObjectsStolen()==this->numberTotalOfObject && square_end.getRect().intersects(*playerRect,rect_intersection)==true){
        this->win=true;
        return true;
    }
    return false;
}

bool Level::checkLoose(){
    gf::Rect<int> rect_intersection;
	gf::Rect<int>* playerRect = player->getRect();
    if(!player->isAStatue()){
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
    Wall square_object = this->map[object[1]][object[0]];
    gf::Rect<int> rect_intersection;

    if(square_object.getRect().intersects(*(this->player->getRect()),rect_intersection)==true && this->map[object[1]][object[0]].getType()==WallType::OBJECT){
        this->player->findObject();
        this->map[object[1]][object[0]].setType(WallType::EMPTY);
    }
}



void Level::checkStatue(){
    Wall square_statue = this->map[statue[1]][statue[0]];
    gf::Rect<int> rect_intersection;
    
    if(square_statue.getRect().intersects(*(this->player->getRect()),rect_intersection)==true){
       	player->allowStatue(true);
       	if(player->isAStatue()){
       		player->setPosition(statue * WALL_SIZE);
       	}
    }else{
    	player->allowStatue(false);
    }
    
}



