#include "level.h"
#include <iostream>

Level::Level(Player & playerLink) : 
	start(Wall({0,0},WallType::START)),
	end(Wall({1*WALL_SIZE.x,1*WALL_SIZE.y},WallType::END)),
	player(playerLink){
	
}

void Level::init(){
	isGameOver = false;
	isWin = false;
	player.setPosition(start.getPosition());
	player.setVelocity({0,0});
}

void Level::load(std::string path){
	currentLevelPath = path;
	objects = {};
	foundObjects = {};
	statues = {};
	
	start = Wall({0,0},WallType::START);
	end = Wall({1*WALL_SIZE.x,1*WALL_SIZE.y},WallType::END);

	map = {};
	FILE* f = fopen(path.c_str(),"r");
	if (f == nullptr){
		std::cout << "Couldn't open "<< path << std::endl;
		exit(1);
		return;
	}

	int width = 0;
	int height = 0;
	char line[128];
	while (fgets(line,128,f)){
		width = strlen(line)-1;
		height++;
	}
	rewind(f);

	//fill level with empty walls
    for(float i = 0; i<height;i++){
        map.push_back({});
        for(float j = 0; j<width;j++){
            gf::Vector2f pos = {j,i};
            pos = pos*WALL_SIZE;
            map[i].push_back(Wall(pos,WallType::EMPTY));
        }
    }
	char c;
	int row = 0;
	int col = 0;
	while(!feof(f)){
		c = getc(f);
		WallType tmp = WallType::EMPTY;
		switch(c){
			case '\0':
				break;
			case '\n':
				row++;
				col = -1;
				break;
			case 's':
				tmp = WallType::START;
				break;
			case 'e':
				tmp = WallType::END;
				break;
			case 'o':
				tmp = WallType::OBJECT;
				break;
			case 't':
				tmp = WallType::STATUE;
				break;
			case '#':
				tmp = WallType::SOLID;
				break;
		}
		if(c=='\0'){break;}
		if(tmp != WallType::EMPTY){
			addWall({col,row},tmp);
		}

		col++;
	}
			
	fclose(f);

}

void Level::reset(){
	isGameOver = false;
	isWin = false;
	player.init();
	player.setPosition(start.getPosition());
	player.setVelocity({0,0});
	//only reset if level loaded at least once
	if(!currentLevelPath.empty()){load(currentLevelPath);};
}


void Level::addWall(gf::Vector2i pos, WallType type){
	if(pos.y < 0 || pos.y >= (int)map.size()){return;}
	if(pos.y < 0 || pos.y >= (int)map.size()){return;}
	Wall newWall = Wall(pos * WALL_SIZE, type);
	if(map[pos.y][pos.x].getType() != WallType::EMPTY){
		std::cout << "Replaced non empty Wall" << std::endl;
		map[pos.y][pos.x] = newWall;
		if(map[pos.y][pos.x].getType() == WallType::EMPTY){
			std::cout << "success" << std::endl;
		}else{
			std::cout << "fail" << std::endl;

		}

	}else{
		map[pos.y][pos.x] = newWall;
	}
	
	switch(type){
		case WallType::OBJECT:
			objects.push_back(newWall);
			break;
		case WallType::STATUE:
			statues.push_back(newWall);
			break;
		case WallType::START:
			start = newWall;
			break;
		case WallType::END:
			end = newWall;
			break;
		default:
			break;	
		
	}
}
void Level::update(gf::Time time){

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
}

gf::RectF Level::findCollider(){
	for(auto& line : map){
		for (auto & wall : line){
			if(wall.getType() == WallType::EMPTY){continue;}
			gf::RectF wallRect = gf::RectF::fromPositionSize(wall.getPosition(),WALL_SIZE);
			gf::RectF playerRect = gf::RectF::fromPositionSize(player.getPosition(),PLAYER_SIZE);

			if(wallRect.intersects(playerRect)){
				//Custom collision code
				doWhenCollide(wall);
				if(wall.getType() == WallType::SOLID){
					return wallRect;
				}
			}
		}
	}
	return gf::RectF::empty();
}

Wall & Level::getWall(int x , int y){
	if(y < 0 || y >= (int)map.size() ||x < 0 || x >= (int)map[y].size() ){
		throw std::out_of_range("Invalid coordinates to getWall");
	}
	return map[y][x];

}

void Level::doWhenCollide(Wall & wall){
	//get grid position of the collided wall
	int x = (int) wall.getPosition().x / WALL_SIZE.x;
	int y = (int) wall.getPosition().y / WALL_SIZE.y;
	switch(wall.getType()){
		case WallType::OBJECT:
			map[y][x].setType(WallType::EMPTY);
			foundObjects.push_back(Wall(wall.getPosition(),WallType::OBJECT));
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
			if(foundObjects.size() == objects.size()){
				isWin=true;
			}else{
				isGameOver = true;
			}
			break;
		default:
			break;	
		
	
	}
}

void Level::render(gf::RenderTarget & target, const gf::RenderStates & states){
	for(auto& line : map){
		for(auto& wall : line){
			wall.render(target);
		}
	}


}

int Level::getNumberTotalObjects(){
    return (int) objects.size();
}
int Level::getNumberStolenObjects(){
    return (int) foundObjects.size();
}	
bool Level::checkGameOver(){
	return isGameOver;
}

bool Level::checkWin(){
	return isWin;
}

