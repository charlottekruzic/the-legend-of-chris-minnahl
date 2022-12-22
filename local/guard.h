#ifndef LOCAL_GUARD_H
#define LOCAL_GUARD_H
#include <gf/Entity.h>
#include <gf/Sprite.h>
#include <gf/Shapes.h>
#include <gf/Event.h>
#include <gf/RenderWindow.h>

constexpr gf::Vector2i GUARD_SIZE = {32,32};


class Guard : public gf::Entity{

    private:
        gf::Vector2f m_position;
        gf::Vector2f m_velocity;
        double speed;
        gf::RectI rect;
        gf::RectangleShape shape;
        gf::Color4f color;

    public:
        Guard(gf::Vector2f spawn);
        virtual void update(float dt);
        virtual void render(gf::RenderTarget& target);
};
#endif