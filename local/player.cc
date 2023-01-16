#include "player.h"
Player::Player(gf::Vector2f spawn) : 
	shape(PLAYER_SIZE),
	leftAction("left"),
	upAction("up"),
	downAction("down"),
	rightAction("right"),
	spaceAction("space")
	 {
    this->speed = 200;
    this->color = gf::Color::Azure;
	//Position du joueur
    this->position = spawn;
	//Utilisé pour les collisions
    this->rect = gf::RectI().fromPositionSize(this->position,PLAYER_SIZE);  
	//Shape = la forme visuelle qui va apparaitre a l'ecran
    this->shape.setColor(this->color);
    this->shape.setAnchor(gf::Anchor::TopLeft);
    this->shape.setPosition(this->position);

	//Add actions
	
	rightAction.addKeycodeKeyControl(gf::Keycode::Right);
	rightAction.setInstantaneous();
	actions.addAction(rightAction);

	leftAction.addKeycodeKeyControl(gf::Keycode::Left);
	leftAction.setInstantaneous();
	actions.addAction(leftAction);

	upAction.addKeycodeKeyControl(gf::Keycode::Up);
	upAction.setInstantaneous();

	actions.addAction(upAction);

	downAction.addKeycodeKeyControl(gf::Keycode::Down);
	downAction.setInstantaneous();
	actions.addAction(downAction);

    spaceAction.addKeycodeKeyControl(gf::Keycode::Space);
    spaceAction.setInstantaneous();
    actions.addAction(spaceAction);

	hasObject=	false;
	isStatue=	false;
	canBeStatue=true;
}

gf::Vector2f Player::getPosition(){
    return this->position;
}

gf::Vector2f Player::getVelocity(){
    return this->velocity;
}

void Player::reset(){
	this->actions.reset();
	this->hasObject=false;
	this->isStatue=false;
}

void Player::setPosition(gf::Vector2f position){
    this->position=position;
    this->shape.setPosition(this->position);
    this->rect = this->rect.fromPositionSize(this->position,PLAYER_SIZE);
}
void Player::setVelocity(gf::Vector2f vel){
    this->velocity=vel;
}

gf::RectI * Player::getRect(){
    return &this->rect;
}

void Player::findObject(){
	this->hasObject=true;
}

bool Player::stoleTheObject(){
	return this->hasObject;
}

bool Player::isAStatue(){
	return this->isStatue;
	
}

void Player::allowStatue(bool val){
	canBeStatue = val;
}

void Player::processEvent(gf::Event event){
	this->actions.processEvent(event);

}

void Player::moveX(float dt){
    this->position.x += this->velocity.x  * dt;
    this->rect = this->rect.fromPositionSize(this->position,PLAYER_SIZE);
    this->shape.setPosition(this->position);
}

void Player::moveY(float dt){
    this->position.y += this->velocity.y  * dt;
    this->rect = this->rect.fromPositionSize(this->position,PLAYER_SIZE);
    this->shape.setPosition(this->position);
}

void Player::handleCollisionX(Wall *collider){
    if(collider==nullptr || this->velocity.x == 0){return;}
    if(this->velocity.x>0){
        //right
        this->setPosition({(collider->getPosition()[0]-PLAYER_SIZE[0]),this->position.y});
    }else{
        //left
        this->setPosition({(collider->getPosition()[0]+WALL_SIZE[0]), this->position.y});
    }
}

void Player::handleCollisionY(Wall *collider){
    if(collider==nullptr || this->velocity.y == 0){return;}
    if(this->velocity.y>0){
        //down
       	this->setPosition( { this->position.x , (collider->getPosition()[1]-PLAYER_SIZE[1])} );
    }else{
        //up
        this->setPosition( { this->position.x , (collider->getPosition()[1]+WALL_SIZE[1]) } );
    }
}


void Player::update(float dt){
	this->velocity = {0.0,0.0};
	if(this->rightAction.isActive()){
		this->velocity.x += this->speed;
	}
	if(this->leftAction.isActive()){
		this->velocity.x -= this->speed;
	}
	if(this->upAction.isActive()){
		this->velocity.y -= this->speed;
	}
	if(this->downAction.isActive()){
		this->velocity.y += this->speed;
	}
	if(spaceAction.isActive() && canBeStatue){
		isStatue = true;
	}else{
		isStatue = false;
	}
}

void Player::render(gf::RenderTarget& target){
    target.draw(this->shape);
};

