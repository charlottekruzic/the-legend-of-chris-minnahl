#include "player.h"
#include <iostream>
Player::Player(gf::ResourceManager& resources)
:resources(resources){
	setPosition({0,0});

	
	isStatue=false;
	dirPlayer=1;
}
void Player::setPosition(gf::Vector2f pos){
	position = pos;
}
gf::Vector2f Player::getPosition(){
	return position;
}

void Player::init(){
	isStatue=false;
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



void Player::setStatue(bool val){
	isStatue = val;
}
bool Player::isAStatue(){
	return isStatue;
}

void Player::setWantToStatue(bool val){
	wantToStatue=  val;
}

bool Player::isWantToStatue(){
	return wantToStatue;
}


void Player::applyXMotion(gf::Time time){
	float dt = time.asSeconds();
	position.x += velocity.x * speed * dt;

}
void Player::applyYMotion(gf::Time time){
	float dt = time.asSeconds();	
	position.y += velocity.y * speed * dt;
}
int Player::setdirectionPlayer(int var){
	dirPlayer=var;
}
void Player::render(gf::RenderTarget & target, const gf::RenderStates & states){
	gf::RectangleShape shape(PLAYER_SIZE);
	gf::Texture& textureRight(resources.getTexture(resources.getAbsolutePath("sprites/player/tile007.png")));
	gf::Texture& textureLeft(resources.getTexture(resources.getAbsolutePath("sprites/player/tile005.png")));
	gf::Texture& textureUp(resources.getTexture(resources.getAbsolutePath("sprites/player/tile002.png")));
	gf::Texture& textureDown(resources.getTexture(resources.getAbsolutePath("sprites/player/tile000.png")));

	shape.setPosition(position);
	target.draw(shape);
	sprite.setAnchor(gf::Anchor::TopLeft);
	sprite.setPosition(position);
	if(dirPlayer==1){
		sprite.setTexture(textureRight);
	}else if(dirPlayer==2){
		sprite.setTexture(textureLeft);
	}else if(dirPlayer==3){
		sprite.setTexture(textureUp);
	}else if(dirPlayer==4){
		sprite.setTexture(textureDown);
	}
	
	target.draw(sprite);

}
