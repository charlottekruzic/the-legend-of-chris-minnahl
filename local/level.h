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
        gf::Vector2i start,end;
        int width,height;
        Player* player;
    public:

        Level(gf::Vector2f size, Player* player,gf::Vector2i start, gf::Vector2i end);
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

        bool isFreeSpace(gf::Vector2i position);

        bool setStart(gf::Vector2i position);

        bool setEnd(gf::Vector2i position);

        void update(float dt);

        void render(gf::RenderTarget& target);

};
#endif
