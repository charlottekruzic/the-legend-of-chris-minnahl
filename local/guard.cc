#include "guard.h"

Guard::Guard(gf::Vector2f spawn):m_velocity(0,0),shape(GUARD_SIZE){
    this->speed = 200;
    this->m_position = spawn;
    this->m_velocity.y = this->speed;
    this->rect = gf::RectI().fromPositionSize(this->m_position,GUARD_SIZE);  
    this->color = gf::Color::Red;
    this->shape.setColor(this->color);
    this->shape.setAnchor(gf::Anchor::TopLeft);
    this->shape.setPosition(this->m_position);
}



void Guard::update(float dt){
    
    
    if(this->m_position.y<10){
        this->m_position.y=10;
        this->m_velocity.y = this->speed;
    } else if(this->m_position.y>300){
        this->m_position.y=300;
        this->m_velocity.y = -this->speed;
    }
    this->m_position += this->m_velocity  * dt;
    this->rect = this->rect.fromPositionSize(this->m_position,GUARD_SIZE);
    this->shape.setPosition(this->m_position);

}

void Guard::render(gf::RenderTarget& target){
    target.draw(this->shape);
};

