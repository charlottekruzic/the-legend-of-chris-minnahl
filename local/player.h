#ifndef LOCAL_PLAYER_H
#define LOCAL_PLAYER_H
#include <gf/Entity.h>
#include <gf/Sprite.h>
#include <gf/Shapes.h>
#include <gf/Event.h>
#include <gf/RenderWindow.h>

constexpr gf::Vector2i PLAYER_SIZE = {32,32};


class Player : public gf::Entity{

    private:
        gf::Vector2f m_position;
        gf::Vector2f m_velocity;
        double speed;
        gf::RectI rect;
        gf::RectangleShape shape;
        gf::Color4f color;

    public:
        Player(gf::Vector2f spawn);
        gf::Vector2f getPosition();
        gf::Vector2f getVelocity();
        gf::RectI getRect();
        void setPosition(gf::Vector2f position);
        void setVelocity(gf::Vector2f velocity);
        void onKeyPress(gf::Event e);
        void onKeyRelease(gf::Event e);
        virtual void update(float dt);
        virtual void render(gf::RenderTarget& target);
};
#endif