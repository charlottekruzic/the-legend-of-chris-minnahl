#ifndef LOCAL_LEVEL_H
#define LOCAL_LEVEL_H
#include <gf/Entity.h>
#include <gf/Sprite.h>
#include <gf/Shapes.h>
#include <gf/RenderWindow.h>
#include "wall.h"
#include "player.h"

class Level{
    private:
        std::vector<std::vector<Wall>> map;
        int width,height;
        Player player;
    public:
        Level(gf::Vector2f size, Player player);
        /**
         * @brief Adds a wall to the level at the given position
         * @param position grid position of the wall
         * @return true if a wall was created
        */
        bool addWall(gf::Vector2i position);

        bool removeWall(gf::Vector2i position);

        void prettyPrint();

        Wall* checkCollisions();

        void handleCollisionX();

        void handleCollisionY();
        
        void update(float dt);

        void render(gf::RenderTarget& target);

};
#endif