#include "minimap.h"
#include <iostream>

Minimap::Minimap(Game& game) 
: m_map(game.getMap())
, m_player(game.getPlayer())
, m_level(game.getLevel())
, m_statues(m_map.getStatues())
, m_not_found_objects(m_level.getNotFoundObjects())
, m_start(m_map.getStart())
, m_end(m_map.getEnd())
{
	
}


void Minimap::update(gf::Time time){
    m_not_found_objects = m_level.getNotFoundObjects();
}

void Minimap::render(gf::RenderTarget & target, const gf::RenderStates & states){
    int y = m_map.getHeight();
	int x = m_map.getWidth();
	for(int row = 0 ; row < y; row++ ){
		for (int col = 0; col<x ; col++){
			m_map.get(col,row).render(target);
		}
	}

	for(Wall & wall : m_statues){
		wall.render(target);
	}

    for(Wall & wall : m_not_found_objects){
		wall.render(target);
	}

	m_map.getStart().render(target);
	m_map.getEnd().render(target);

    m_player.render(target, states);
}




