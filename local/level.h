#ifndef LOCAL_LEVEL_H
#define LOCAL_LEVEL_H
#include <gf/Entity.h>
#include <gf/Sprite.h>
#include <gf/Shapes.h>
#include <gf/RenderWindow.h>
#include "wall.h"

class Level{
    private:
        std::vector<std::vector<Wall>> map;
        
        int width,height;
    public:
        Level(gf::Vector2f size);
        /**
         * @brief Adds a wall to the level at the given position
         * @param position grid position of the wall
         * @return true if a wall was created
        */
        bool addWall(gf::Vector2i position);

        bool removeWall(gf::Vector2i position);

        void prettyPrint();
        
        void update(float dt);

        void render(gf::RenderTarget& target);

};
#endif