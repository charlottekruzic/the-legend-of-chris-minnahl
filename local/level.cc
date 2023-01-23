#include "level.h"
#include <iostream>

Level::Level(Player & playerLink) : 
	start(Wall({0,0},WallType::START)),
	end(Wall({1*WALL_SIZE.x,1*WALL_SIZE.y},WallType::END)),
	player(playerLink){
	
}

void Level::init(){
	isGameOver = false;
	player.setPosition(start.getPosition());
	player.setVelocity({0,0});
}

void Level::load(std::string path){
	objects = {};
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


void Level::addWall(gf::Vector2i pos, WallType type){
	if(pos.y < 0 || pos.y >= (int)map.size()){return;}
	if(pos.y < 0 || pos.y >= (int)map.size()){return;}
	Wall newWall = Wall(pos * WALL_SIZE, type);
	map[pos.y][pos.x] = newWall;
	if(type == WallType::OBJECT){
		objects.push_back(newWall);
	}
	if(type == WallType::STATUE){
		statues.push_back(newWall);
	}
	if(type == WallType::START){
		start = newWall;
	}
	if(type == WallType::END){
		end = newWall;
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
		for (auto& wall : line){
			if(wall.getType() != WallType::SOLID && wall.getType()!= WallType::END){continue;}
			gf::RectF wallRect = gf::RectF::fromPositionSize(wall.getPosition(),WALL_SIZE);
			gf::RectF playerRect = gf::RectF::fromPositionSize(player.getPosition(),PLAYER_SIZE);

			if(wallRect.intersects(playerRect)){
				if(wall.getType() == WallType::END){
					isGameOver = true;
				}
				return wallRect;
			}
		}
	}
	return gf::RectF::empty();
}

void Level::render(gf::RenderTarget & target,
					const gf::RenderStates & states){
	for(auto& line : map){
		for(auto& wall : line){
			if (wall.getType() != WallType::EMPTY){
				wall.render(target);
			}
		}
	}	
}	
bool Level::checkGameOver(){
	return isGameOver;
}
