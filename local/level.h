#ifndef LOCAL_LEVEL_H
#define LOCAL_LEVEL_H
#include <gf/Entity.h>
#include <gf/Sprite.h>
#include <gf/Shapes.h>
#include <gf/RenderWindow.h>
#include <gf/Text.h>
#include <gf/Font.h>
#include <string>
#include "wall.h"
#include "player.h"
#include "guard.h"

class Level{
    private:
        std::vector<std::vector<Wall>> map;
        gf::Vector2i start,end,object,statue;
        int width,height;
        Player* player;
        bool win, loose;
        std::vector<Guard*> guards;
        gf::RectangleShape background;
        std::string level_path;
        int numberTotalOfObject=0;
    public:
        Level(Player* player,std::string path);
        /**
         * @brief Adds a wall to the level at the given position
         * @param position grid position of the wall
         * @return true if a wall was created
        */

        
        bool addWall(gf::Vector2i position);

		/**
		*@brief Load a level from a text file.
		*@param path to the text file from root directory
		*/
		void load(std::string path);

        gf::Vector2f getSize();

        float getWidth();

        float getHeight();

		Guard * addGuard(gf::Vector2i grid_pos,std::vector<RouteAction *> route);

        void reset();

        bool isWin();

        bool isLoose();


        bool removeWall(gf::Vector2i position);

        void prettyPrint();

        Wall* checkCollisions();

        bool checkWin();

        bool checkLoose();


        void checkTakeObject();

        void checkStatue();

        bool isFreeSpace(gf::Vector2i position);

        bool setStart(gf::Vector2i position);

        bool setEnd(gf::Vector2i position);

        bool setObject(gf::Vector2i pos);

        bool setStatue(gf::Vector2i pos);

        void update(float dt);

        void render(gf::RenderTarget& target, bool isMinimap);

        void renderScore(gf::RenderTarget& target, gf::Vector2f size);

};
#endif
