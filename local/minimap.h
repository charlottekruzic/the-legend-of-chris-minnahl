#ifndef LOCAL_MINIMAP_H
#define LOCAL_MINIMAP_H

#include "map.h"
#include "player.h"
#include "wall.h"
#include "level.h"
#include "../scenes/game.h"

class Minimap : public gf::Entity{
	private:
		Map& m_map; 
        Player& m_player;
        Level& m_level;
        std::vector<std::vector<Wall>> m_walls;
        std::vector<Wall> m_statues;
        std::vector<Wall> m_not_found_objects;
		Wall m_start, m_end;
		
	public:
		Minimap(Game& game) ;
        virtual void render(gf::RenderTarget & target, const gf::RenderStates & states);
        void update(gf::Time time);
		

};		
#endif
