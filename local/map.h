#ifndef LOCAL_MAP_H
#define LOCAL_MAP_H
#include "wall.h"
#include "player.h"
#include "guard.h"
#include <string.h>

class Map{
	private:
		std::vector<std::vector<Wall>> data;
		std::vector<Wall> objects;
		std::vector<Wall> statues;
		Wall start,end;
		int width,height;
	public :
		Map();
		void load(std::string);
		void set(gf::Vector2i position,WallType type);	
		Wall & get(int x, int y);
		Wall & getStart();
		Wall & getEnd();
		std::vector<Wall> & getObjects();
		std::vector<Wall> & getStatues();
		int getHeight();
		int getWidth();

			
	
};

#endif
