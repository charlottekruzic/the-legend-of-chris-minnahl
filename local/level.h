#ifndef LOCAL_LEVEL_H
#define LOCAL_LEVEL_H
#include <gf/Entity.h>
#include <gf/Sprite.h>
#include <gf/Shapes.h>
#include <gf/RenderWindow.h>
#include <gf/Text.h>
#include <gf/Font.h>
#include <gf/Widgets.h>
#include <string.h>
#include "wall.h"
#include "player.h"
#include "guard.h"

class Level : public gf::Entity{
	private:
		std::vector<std::vector<Wall>> map;
		std::vector<Wall> objects;
		std::vector<Wall> foundObjects;
		std::vector<Wall> statues;

		Wall start;
		Wall end;
		
		Player& player;
		bool isGameOver;
		bool isWin;
		std::string currentLevelPath;
		
	public:
		Level(Player & player);
		void init();
		void load(std::string path);
		void reset();
		virtual void render(gf::RenderTarget & target,
		const gf::RenderStates & states);	
		void addWall(gf::Vector2i position,WallType type);	
		Wall & getWall(int x, int y);
		void update(gf::Time time);
		//find collider rect
		gf::RectF findCollider();
		//custom code to do once collided with a non empty wall
		void doWhenCollide(Wall & wall);
		bool checkGameOver();
		bool checkWin();
		int getNumberTotalObjects();
		int getNumberStolenObjects();
};		
#endif
