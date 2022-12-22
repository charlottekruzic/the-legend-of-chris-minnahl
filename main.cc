#include <iostream>
#include <gf/Event.h>
#include <gf/Font.h>
#include <gf/RenderWindow.h>
#include <gf/Sprite.h>
#include <gf/Text.h>
#include <gf/Window.h>
#include <gf/Entity.h>
#include <gf/Shapes.h>
#include <Box2D/Box2D.h>
//Include external classes
#include "local/player.h"
#include "local/level.h"

constexpr int WORLD_SIZE = 20;

class Game{
    public:
        Game() :
        window("My awesome game",{ 1280, 720}),
        renderer(window),player({128,128}),
        level({WORLD_SIZE,WORLD_SIZE}, &player){
        	for(int y = 0; y<WORLD_SIZE ; y++){
        		for(int x : {0,WORLD_SIZE-1}){
            		this->level.addWall({x,y});
            		this->level.addWall({y,x});

        		}
        	}
            this->gameloop();
        }
    private: 
        Player player;
        gf::Window window;
        gf::RenderWindow renderer;
        Level level;

        void gameloop(){
            this->renderer.clear(gf::Color::Gray(0.3));
            gf::Clock clock;
            
            gf::Font font("arial.ttf");
            gf::Text gameOverText("GAME OVER", font);           
            gameOverText.setCharacterSize(30);
            gameOverText.setPosition({100,100});
            gameOverText.setColor(gf::Color::Red);
            
            while (this->window.isOpen()) {
                // Process events
                gf::Event event;
            
                while (this->window.pollEvent(event)) {
                    switch (event.type) {
                        case gf::EventType::Closed:
                            this->window.close();
                            break;
                        case gf::EventType::KeyPressed:
                            if(event.key.keycode == gf::Keycode::P){
                                this->level.prettyPrint();
                                break;
                            }
                            this->player.onKeyPress(event);
                            break;
                        case gf::EventType::KeyReleased:
                            this->player.onKeyRelease(event);
                            break;
                        default:
                        break;
                    }
                }

                //Update
                float dt = clock.restart().asSeconds();
                this->player.update(dt);
                this->level.update(dt);

                // Draw the entities
                this->renderer.clear();
                this->level.render(this->renderer);
                this->player.render(this->renderer);
                //this->renderer.draw(gameOverText);
                this->renderer.display();
                
            }
        }


};

int main() {
  Game game;
  return 0;
}
