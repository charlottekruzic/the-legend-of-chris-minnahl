#include "label.h"

Label::Label() : Panel(), font("../arial.ttf"){
	this->text.setFont(this->font);
	this->text.setAnchor(gf::Anchor::TopLeft);
	this->setText("");
	this->setTextColor(gf::Color::Black);
}


Label::Label(std::string string) : Label(){
	this->setText(string);
}


void Label::setText(std::string string){
	this->text.setString(string);
	this->text.setPosition(this->position);
}
std::string Label::getText()const{
	return this->text.getString();
}

void Label::setTextColor(gf::Color4f newColor){
	this->text.setColor(newColor);
}

void Label::render(gf::RenderTarget& target){
	//Panel::render(target);
	target.draw(this->shape);
	this->text.draw(target,{});
}
