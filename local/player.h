#ifndef LOCAL_PLAYER_H
#define LOCAL_PLAYER_H
#include <gf/Entity.h>
#include <gf/Math.h>
#include <gf/Shapes.h>
#include <gf/Action.h>
#include <gf/Event.h>
#include <gf/RenderWindow.h>
#include <gf/Time.h>

constexpr gf::Vector2f PLAYER_SIZE = {32.0,32.0};


class Player: public gf::Entity{
	private:
	gf::Vector2f position;
	gf::Vector2f velocity;
	gf::Action spaceAction;
	gf::ActionContainer actions;
	int numberOfObjects=0;
	float speed = 200.0;
	bool isStatue,canBeStatue;
	public :
		Player();

		void reset();
		void setPosition(gf::Vector2f position);
		gf::Vector2f getPosition();
		void setVelocity(gf::Vector2f vel);
		gf::Vector2f getVelocity();
		void addVelocity(gf::Vector2f vel);
		void findObject();
		int NumberOfObjectsStolen();
		//allow player to be a statue
        void allowStatue(bool val);
		//check if player is currently a statue
        bool isAStatue();
		void processEvent(gf::Event);
		void applyXMotion(gf::Time time);
		void applyYMotion(gf::Time time);
		void doHandleActions(gf::Window & window);
		virtual void update(gf::Time time);
		virtual void render(gf::RenderTarget & target,
		const gf::RenderStates & states);
		
};
#endif
