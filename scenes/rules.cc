#include "rules.h"
#include "../manager.h"
#include <iostream>
#include <gf/Color.h>


Rules::Rules(gf::Vector2i size,Manager& link) :
	Scene(size),spaceAction("Press_space"),managerLink(link){
	setClearColor(gf::Color::Orange);
	
	spaceAction.addKeycodeKeyControl(gf::Keycode::Space);
	addAction(spaceAction);
}

void Rules::doHandleActions(gf::Window & window){
	if(spaceAction.isActive()){
		managerLink.replaceScene(managerLink.titleScene);

	}
}

