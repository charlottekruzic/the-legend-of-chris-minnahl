#ifndef LOCAL_LEVEL_H
#define LOCAL_LEVEL_H
#include <gf/Entity.h>
#include <gf/Sprite.h>
#include <gf/Shapes.h>
#include <gf/RenderWindow.h>
#include <gf/Text.h>
#include <gf/Font.h>
#include <gf/Widgets.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include "wall.h"
#include "player.h"
#include "guard.h"
#include "map.h"
class Level : public gf::Entity{
	private:
		Map& map;
		Player& player;
		bool isGameOver;
		bool isWin;
		std::vector<Wall> foundObjects;
		std::vector<Wall> notFoundObjects;
	public:
		Level(Player & player, Map & map);
		void reset();
		virtual void render(gf::RenderTarget & target,
		const gf::RenderStates & states);	

		void update(gf::Time time);
		//find collider rect
		gf::RectF findCollider();
		//custom code to do once collided with a non empty wall
		void doWhenCollide(Wall & wall);
		bool checkGameOver();
		bool checkWin();
		std::vector<Wall> & getFoundObjects();
		std::vector<Wall> & getNotFoundObjects();

		gf::RectF testCollision(Wall & wall);
};		
#endif
