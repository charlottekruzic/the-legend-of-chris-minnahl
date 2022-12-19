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



class Game{
    private: 
        Player player;
        gf::Window window;
        gf::RenderWindow renderer;
    public:
        Game() : window("My awesome game", { 640, 480 }),renderer(window),player({100,100}){        
            this->gameloop();
        }

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

                // Draw the entities
                this->renderer.clear();

                this->player.render(this->renderer);
                this->renderer.draw(gameOverText);
                
                
                this->renderer.display();
            }
        }
};

int main() {
  Game game;
  return 0;
}