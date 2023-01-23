#include "player.h"
#include <iostream>
Player::Player(){
	setPosition({0,0});
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
void Player::setVelocity(gf::Vector2f vel){
	velocity = vel;
}
gf::Vector2f Player::getVelocity(){
	return velocity;
}
void Player::addVelocity(gf::Vector2f vel){
	velocity += vel;
}

void Player::applyXMotion(gf::Time time){
	float dt = time.asSeconds();
	position.x += velocity.x * speed * dt;

}
void Player::applyYMotion(gf::Time time){
	float dt = time.asSeconds();	
	position.y += velocity.y * speed * dt;
}
