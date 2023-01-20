#ifndef TITLE_H
#define TITLE_H
#include <gf/Scene.h>
#include <gf/Math.h>
#include <gf/Time.h>
#include <gf/Action.h>
struct Manager;

class Title : public gf::Scene {
	private:
	gf::Action spaceAction; 
	Manager * managerLink;


	public:
	Title(gf::Vector2i size);
	void doHandleActions(gf::Window & window);
	void setManager(Manager * m);
};

#endif
