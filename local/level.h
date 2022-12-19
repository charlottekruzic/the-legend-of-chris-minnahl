#ifndef LOCAL_LEVEL_H
#define LOCAL_LEVEL_H
#include <gf/Entity.h>
#include <gf/Sprite.h>
#include <gf/Shapes.h>
#include <gf/RenderWindow.h>

class Level{
    private:
        int map [[]];

    public:
        Level(gf::Vector2i size);
        bool addWall(gf::Vector2i position);
        bool removeWall(gf::Vector2i position);
        virtual void update(float dt);
        virtual void render(gf::RenderTarget& target);

};
#endif