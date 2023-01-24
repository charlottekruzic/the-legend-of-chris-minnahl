#ifndef LOCAL_PANEL_H
#define LOCAL_PANEL_H
#include <gf/Action.h>
#include <gf/Entity.h>
#include <gf/Sprite.h>
#include <gf/Shapes.h>
#include <gf/Event.h>
#include <gf/RenderWindow.h>


class Panel : public gf::Entity{
	protected:
	gf::Vector2f position;
	gf::Vector2f size;
	gf::Color4f color;
	gf::RectangleShape shape;
	gf::RectI rect;	

	public:
	Panel();
	void setPosition(gf::Vector2f pos);
	void setSize(gf::Vector2f newSize);
	gf::Vector2f getPosition();
	void setColor(gf::Color4f color);

	void update(float dt);
	void render(gf::RenderTarget& target);
	
};



#endif
