#include "button.h"

Button::Button(std::string string, gf::v1::Vector2f position, float size_text, gf::Color4f background_color, gf::Font &font): button(string, font, size_text){
    this->button.setBackgroundOutlineThickness(2);
    this->button.setDefaultBackgroundColor(background_color);
    this->button.setPadding(10.0);
    this->button.setRadius(12.0);
    this->button.setPosition(position);
}

gf::TextButtonWidget Button::getButton(){
    return this->button;
}