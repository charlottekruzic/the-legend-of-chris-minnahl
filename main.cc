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
#include "local/guard.h"
#include "gui/panel.h"
#include "gui/label.h"
constexpr int WORLD_SIZE = 20;

class Game{
    public:
        Game() :
        window("My awesome game",{ 1280, 720}),
        renderer(window),
        player({128,128}),//Initialize player

        level({WORLD_SIZE,WORLD_SIZE},&player,{2,2},{10,15})//initialize level with set size, pointer to player and start/end grid coordinates
        {
            this->isFinished = false;
            this->win = false;
        	for(int y = 0; y<WORLD_SIZE ; y++){//fill the level borders with walls
        		for(int x : {0,WORLD_SIZE-1}){
            		this->level.addWall({x,y});
            		this->level.addWall({y,x});
        		}
        	}
        	this->level.addWall({5,5});
        	this->level.addWall({5,6});
            this->gameloop();
        }
    private: 
        Player player;
        gf::Window window;
        gf::RenderWindow renderer;
        Level level;
        bool isFinished = true;
        bool win = true;
        

        void gameloop(){
            this->renderer.clear(gf::Color::Gray(0.3));
            gf::Clock clock;
            gf::Font font("arial.ttf");
            gf::Text gameOverText("GAME OVER", font);           
            gameOverText.setCharacterSize(30);
            gameOverText.setPosition({100,100});
            gameOverText.setColor(gf::Color::Red);
            gf::Text winText("Won", font);           
            winText.setCharacterSize(30);
            winText.setPosition({100,100});
            winText.setColor(gf::Color::Red);
            gf::Text pressSpaceText("Press space to start over", font);           
            pressSpaceText.setCharacterSize(30);
            pressSpaceText.setPosition({250,600});
            pressSpaceText.setColor(gf::Color::Red);
            Label p("HELLO");
            p.setSize({300,300});
            p.setPosition({600,200});
            p.setColor(gf::Color::Cyan);
           	Guard guard1({260,90});//Initialize guard1
        	Guard guard2({400,200});//initialize guard2
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
						default:
							break;
                    }
                    this->player.processEvent(event);
                }

                if(this->level.isWin()){
                    this->endgame();
                }

                if(isFinished == false){
                    //Update
                    float dt = clock.restart().asSeconds();
                    this->player.update(dt);
                    guard1.update(dt);
                    guard2.update(dt);
                    this->level.update(dt);
                }

                // Draw the entities
                this->renderer.clear();
                this->level.render(this->renderer);
                this->player.render(this->renderer);
                guard1.render(this->renderer);
                guard2.render(this->renderer);
                p.render(this->renderer);
                //if the game is over
                if(this->isFinished == true){
                    //if he lost
                    if(this->win == false){
                        this->renderer.draw(gameOverText);
                    }else{
                        this->renderer.draw(winText);
                    }
                    this->renderer.draw(pressSpaceText);
                    while (window.pollEvent(event)) {
                        switch (event.type) {
                        case gf::EventType::Closed:
                            this->window.close();
                            break;
                        case gf::EventType::KeyPressed:
                            if(event.key.keycode == gf::Keycode::Space){
                                this->startgame();
                                break;
                            }
						default:
							break;
                    }
                    
                    }
                }
                
                this->renderer.display();
            }
        }

        void startgame(){
            this->level.reset();
            //printf("main APRES velocity x : %f",this->player.getVelocity()[0]);
            //printf("main APRES velocity y : %f",this->player.getVelocity()[1]);
            this->isFinished=false;
        }
        
        void endgame(){
            //printf("main AVANT velocity x : %f",this->player.getVelocity()[0]);
            //printf("main AVANT velocity y : %f",this->player.getVelocity()[1]);
            this->isFinished=true;
        }

};

int main() {
  Game game;
  return 0;
}
