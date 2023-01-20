#include "title.h"
#include <iostream>
#include <gf/Color.h>

#include "../manager.h"

Title::Title(gf::Vector2i size) : Scene(size),spaceAction("Press_space") {
	setClearColor(gf::Color::Azure);
	
	spaceAction.addKeycodeKeyControl(gf::Keycode::Space);
	addAction(spaceAction);
}

void Title::doHandleActions(gf::Window & window){
	if(spaceAction.isActive()){
		managerLink->replaceScene(managerLink->rulesScene);
	}
}

void Title::setManager(Manager * m){
	managerLink = m;
}
