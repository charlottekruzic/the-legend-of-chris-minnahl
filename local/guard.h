#ifndef LOCAL_GUARD_H
#define LOCAL_GUARD_H
#include <gf/Entity.h>
#include <gf/Sprite.h>
#include <gf/Shapes.h>
#include <gf/Event.h>
#include <gf/RenderWindow.h>

constexpr gf::Vector2i GUARD_SIZE = {32,32};
constexpr gf::Vector2i DETECTOR_SIZE = {80,80};


enum class actionType{GO,WAIT};

struct RouteAction{
	actionType type;
	float time;
	float cumulated_time;
	gf::Vector2i grid_position;
	
};

struct RouteAction * generateRouteAction(actionType type,float time,gf::Vector2i position);

class Guard : public gf::Entity{

    private:
    	std::vector<struct RouteAction *> route;
    	int route_index;
    	
        gf::Vector2f position, last_position, spawn_position;
        double speed;
        gf::RectI rect;
        gf::RectangleShape shape;
        gf::Color4f color;
        gf::RectI detectorRect;
        gf::RectangleShape detectorShape;
        struct RouteAction * currentAction;
    public:
        Guard(gf::Vector2i grid_pos);
        void reset();
		void nextAction();
        void setRoute(std::vector<struct RouteAction *> route);
        virtual void update(float dt);
        virtual void render(gf::RenderTarget& target);
        gf::RectI * getRect();
};
#endif
