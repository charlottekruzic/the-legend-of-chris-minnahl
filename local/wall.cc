#include "wall.h"
  
Wall::Wall(gf::Vector2f position,WallType type){
    this->m_position = position;
    //Set up the collider rect
    this->rect = gf::RectI().fromPositionSize(this->m_position,WALL_SIZE);

	//Set up the shape (visual representation of the player)
    this->shape.setAnchor(gf::Anchor::TopLeft);
    this->shape.setPosition(this->m_position);
    this->shape.setSize(WALL_SIZE);

	//Sets the type of wall, (solid ?, color?)
    this->setType(type);
}

bool Wall::setType(WallType type){
    switch(type){
        case WallType::Empty:
            this->solid = false;
            this->color = gf::Color::Red;
            break;
        case WallType::Solid:
            this->solid = true;
            this->color = gf::Color::Green;

            break;
        default:
            return false;
    }
    this->shape.setColor(this->color);

    this->type = type;

    return true;
}

bool Wall::isSolid(){
    return this->solid;
}
void Wall::render(gf::RenderTarget& target){
    if(this->type == WallType::Empty){
        return;
    }
    target.draw(this->shape);
}
