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
//Include local headers
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


			//Set actions
			
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


			gf::ActionContainer actions;

			gf::Action closeWindowAction("Close window");
			closeWindowAction.addCloseControl();
			closeWindowAction.addKeycodeKeyControl(gf::Keycode::Escape);
			actions.addAction(closeWindowAction);

			gf::Action spaceAction("Press Space");
			spaceAction.addKeycodeKeyControl(gf::Keycode::Space);
			actions.addAction(spaceAction);

            
            gf::Clock clock;
            gf::Font font("arial.ttf");

            //Text 
            gf::Text gameOverText("GAME OVER", font);           
            gf::Text pressSpaceText("Press space to start over", font);
            gf::Text winText("Won", font);           
			
            //Set
            gameOverText.setCharacterSize(30);
            gameOverText.setPosition({100,100});
            gameOverText.setColor(gf::Color::Red);
            
            winText.setCharacterSize(30);
            winText.setPosition({100,100});
            winText.setColor(gf::Color::Red);
            
            pressSpaceText.setCharacterSize(30);
            pressSpaceText.setPosition({250,600});
            pressSpaceText.setColor(gf::Color::Red);

            level.addGuard(
				{
            	generateRouteAction(actionType::WAIT,2.0,{1,1}),
            	generateRouteAction(actionType::GO,1.0,{1,1}),
            	generateRouteAction(actionType::WAIT,2.0,{1,1}),

				}
            );
            
        	float dt;
        	
            while (this->window.isOpen()) {
                // Process events
                gf::Event event;
            
                while (this->window.pollEvent(event)) {
                    actions.processEvent(event);
                    this->player.processEvent(event);
                }

                
			    if(closeWindowAction.isActive()) {
			      this->window.close();
			 	}

			    if(spaceAction.isActive() && isFinished) {
			      this->startGame();
			 	}

			 	
                if(this->level.isWin()){
                    this->endgame();
                }
                
                dt = clock.restart().asSeconds();

                if(isFinished == false){
                    //Update
                    this->player.update(dt);
                    this->level.update(dt);
                }

                // Draw the entities
                this->renderer.clear();
                this->level.render(this->renderer);
                this->player.render(this->renderer);

                
                //if the game is over
                if(this->isFinished == true){
                    //if he lost
                    if(this->win == false){
                        this->renderer.draw(gameOverText);
                    }else{
                        this->renderer.draw(winText);
                    }
                    this->renderer.draw(pressSpaceText);
                }
                
                this->renderer.display();
                actions.reset();

            }
            
        }

        void startGame(){
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
