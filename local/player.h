#ifndef LOCAL_PLAYER_H
#define LOCAL_PLAYER_H
#include <gf/Entity.h>
#include <gf/Math.h>
#include <gf/Shapes.h>
#include <gf/RenderWindow.h>
#include <gf/Time.h>

class Player: public gf::Entity{
	private:
	gf::Vector2f position;
	gf::Vector2f velocity;
	float speed = 10.0;
	public :
		Player();
		virtual void update(gf::Time time);
		virtual void render(gf::RenderTarget & target,
				const gf::RenderStates & states);	

		void setPosition(gf::Vector2f position);
		gf::Vector2f getPosition();
		void setVelocity(gf::Vector2f vel);
		gf::Vector2f getVelocity();
		void addVelocity(gf::Vector2f vel);
		
};
#endif
