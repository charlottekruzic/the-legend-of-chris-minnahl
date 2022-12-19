#ifndef LOCAL_WALL_H
#define LOCAL_WALL_H
#include <gf/Entity.h>
#include <gf/Sprite.h>
#include <gf/Shapes.h>
#include <gf/RenderWindow.h>

#define WALL_SIZE 32

class Wall : public gf::Entity{
    private:
        gf::Vector2f m_position;
        gf::RectI rect;
        gf::RectangleShape shape;
        gf::Color4f color;

    public:
        Wall(gf::Vector2f position);
        void render(gf::RenderTarget& target);
};
#endif