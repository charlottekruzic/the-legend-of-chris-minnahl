#include "player.h"

Player::Player(){
	setPosition({0,0});
}
void Player::setPosition(gf::Vector2f pos){
	position = pos;
}

void Player::render(gf::RenderTarget & target, const gf::RenderStates & states){
	gf::RectangleShape shape({32.0,32.0});
	shape.setPosition(position);
	target.draw(shape);
}
void Player::update(gf::Time time){
	float dt = time.asSeconds();	
	position += velocity * speed * dt;
		
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
