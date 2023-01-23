#include "player.h"
#include <iostream>
Player::Player():spaceAction("space"){
	setPosition({0,0});

	spaceAction.addKeycodeKeyControl(gf::Keycode::Space);
    spaceAction.setInstantaneous();
	actions.addAction(spaceAction);

	this->isStatue=false;
	this->canBeStatue=true;
}
void Player::setPosition(gf::Vector2f pos){
	position = pos;
}
gf::Vector2f Player::getPosition(){
	return position;
}
void Player::render(gf::RenderTarget & target, const gf::RenderStates & states){
	gf::RectangleShape shape(PLAYER_SIZE);
	shape.setPosition(position);
	target.draw(shape);
}
void Player::update(gf::Time time){
	
}
void Player::reset(){
	this->numberOfObjects=0;
	this->actions.reset();
	this->isStatue=false;
}



void Player::setVelocity(gf::Vector2f vel){
	velocity = vel;
}
gf::Vector2f Player::getVelocity(){
	return velocity;
}
void Player::addVelocity(gf::Vector2f vel){
	velocity += vel;
}

void Player::findObject(){
	this->numberOfObjects++;
}

int Player::NumberOfObjectsStolen(){
	return this->numberOfObjects;
}

bool Player::isAStatue(){
	return this->isStatue;
	
}

void Player::allowStatue(bool val){
	this->canBeStatue = val;
}

void Player::processEvent(gf::Event event){
	this->actions.processEvent(event);

}

void Player::applyXMotion(gf::Time time){
	float dt = time.asSeconds();
	position.x += velocity.x * speed * dt;

}
void Player::applyYMotion(gf::Time time){
	float dt = time.asSeconds();	
	position.y += velocity.y * speed * dt;
}

void Player::doHandleActions(gf::Window & window){
	if(spaceAction.isActive() && this->canBeStatue){
		this->isStatue = true;
		std::cout << "statue" << "\n";
	}else{
		this->isStatue = false;
	}
}
