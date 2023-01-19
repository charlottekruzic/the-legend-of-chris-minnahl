#ifndef RULES_H
#define RULES_H
#include <gf/Scene.h>
#include <gf/Math.h>
#include <gf/Time.h>
#include <gf/Action.h>
#include "../manager.h"

class Rules : public gf::Scene {
	private:
	gf::Action spaceAction; 
	Manager* managerLink;
	public:
	Rules(gf::Vector2i size);
	void doUpdate(gf::Time time);
	void doHandleActions(gf::Window & window);
	void setManager(Manager* m);

};

#endif
