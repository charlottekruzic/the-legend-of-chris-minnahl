#ifndef LOCAL_WALL_H
#define LOCAL_WALL_H
#include <gf/Entity.h>
#include <gf/Sprite.h>
#include <gf/Shapes.h>
#include <gf/RenderWindow.h>
#include <iostream>
constexpr gf::Vector2f WALL_SIZE = {32.0,32.0};

/** 
 * @brief Abstract class for all types of walls
*/
enum class WallType {SOLID,EMPTY,START,END,OBJECT,STATUE};

class Wall : public gf::Entity{
    protected:
        gf::Vector2f m_position;
        gf::RectI rect;
        gf::RectangleShape shape;
        gf::Color4f color;
        bool solid;
        WallType type;


    public:
        /**
         * @brief Default constructor
         * @param position world coordinates of the wall (topleft)
        */
        Wall(gf::Vector2f position,WallType type);

        gf::RectI getRect();

        gf::Vector2f getPosition();
        
		WallType getType()const;

        void render(gf::RenderTarget& target);

        /** 
         * @brief checks if the wall has collisions
        * @return true if the wall has collision, false otherwise
        */
        bool isSolid();

        bool setType(WallType type);
};

#endif
