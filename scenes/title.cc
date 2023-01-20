#include "title.h"
#include <iostream>

#include "../manager.h"

Title::Title(gf::Vector2i size,Manager& link) :
	Scene(size),spaceAction("Press_space"),managerLink(link){
	setClearColor(gf::Color::Azure);
	
	spaceAction.addKeycodeKeyControl(gf::Keycode::Space);
	addAction(spaceAction);

	this->titleMenu = gf::Text("The Legend Of Chris Minnahl", font);
	this->titleMenu.setCharacterSize(50);
	gf::Coordinates coordinates_title(WINDOW_SIZE);
	gf::Vector2f center = coordinates_title.getCenter();
	this->titleMenu.setPosition(coordinates_title.getAbsolutePoint(center/2, gf::Anchor::TopLeft));
	this->titleMenu.setColor(gf::Color::Cyan);

	
	this->button1.setAnchor(gf::Anchor::Center);
	this->button1.setPosition({WINDOW_SIZE[0]/2 ,300.0});
	
	this->button2.setAnchor(gf::Anchor::Center);
	this->button2.setPosition({WINDOW_SIZE[0]/2,400.0});

	this->button3.setAnchor(gf::Anchor::Center);
	this->button3.setPosition({WINDOW_SIZE[0]/2,500.0});

	this->buttons.push_back(button1);
	this->buttons.push_back(button2);
	this->buttons.push_back(button3);

	for(int i=0;i<3;i++){
		this->buttons[i].setBackgroundOutlineThickness(2);
		this->buttons[i].setDefaultBackgroundColor(gf::Color::Cyan);
		this->buttons[i].setPadding(20.0);
		this->buttons[i].setRadius(12.0);
	}
	
	
}

void Title::doHandleActions(gf::Window & window){
	if(spaceAction.isActive()){
		managerLink.replaceScene(managerLink.gameScene);
	}
}
void Title::doUpdate (gf::Time time){

}
void Title::doRender (gf::RenderTarget &target, const gf::RenderStates &states){
	target.draw(this->titleMenu);
	for(int i=0;i<3;i++){
		target.draw(this->buttons[i]);
	}
}