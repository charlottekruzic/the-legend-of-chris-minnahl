#include "title.h"
#include <iostream>
#include <gf/Color.h>

#include "../manager.h"

Title::Title(gf::Vector2i size,Manager& link) :
	Scene(size),spaceAction("Press_space"),managerLink(link){
	setClearColor(gf::Color::Azure);
	
	spaceAction.addKeycodeKeyControl(gf::Keycode::Space);
	addAction(spaceAction);
}

void Title::doHandleActions(gf::Window & window){
	if(spaceAction.isActive()){
		managerLink.replaceScene(managerLink.rulesScene);
	}
}
