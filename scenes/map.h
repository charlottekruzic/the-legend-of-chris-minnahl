#ifndef MAP_H
#define MAP_H

#include <gf/Scene.h>
#include <gf/Action.h>

struct Manager;




class Map : public gf::Scene {
	private:
		Manager& m_managerLink;
        gf::Action m_mAction;

	
	public:
		Map(gf::Vector2i size,Manager& link);
        void doHandleActions(gf::Window & window) override;
	
};

#endif