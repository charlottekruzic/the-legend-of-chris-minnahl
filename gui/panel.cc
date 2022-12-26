#include "panel.h"


Panel::Panel(){
    this->shape.setAnchor(gf::Anchor::TopLeft);
	this->setPosition({0,0});
	this->setSize({100,100});
	this->setColor(gf::Color::Blue);
};

void Panel::setPosition(gf::Vector2f pos){
	this->position = pos;
	this->rect = gf::RectI().fromPositionSize(this->position,this->size);
    this->shape.setPosition(this->position);
};

void Panel::setSize(gf::Vector2f newSize){
	this->size = newSize;
	this->rect = gf::RectI().fromPositionSize(this->position,newSize); 
	this->shape = gf::RectangleShape(newSize);
	this->shape.setAnchor(gf::Anchor::TopLeft);

    this->shape.setPosition(this->position);
    this->setColor(this->color);
}

gf::Vector2f Panel::getPosition(){
	return this->position;
}

void Panel::setColor(gf::Color4f newColor){
	this->color = newColor;
	this->shape.setColor(this->color);

};

void Panel::update(float dt){};

void Panel::render(gf::RenderTarget& target){
	target.draw(this->shape);
};
