#include <iostream>
#include <gf/Event.h>
#include <gf/Font.h>
#include <gf/RenderWindow.h>
#include <gf/Sprite.h>
#include <gf/Text.h>
#include <gf/Window.h>
#include <gf/Entity.h>
#include <gf/Shapes.h>
#include <gf/View.h>
#include <gf/Rect.h>
#include <Box2D/Box2D.h>
//Include local headers
#include "local/player.h"
#include "local/level.h"
#include "local/guard.h"
#include "gui/panel.h"
#include "gui/label.h"
#include "gui/button.h"
#include <gf/Widgets.h>

constexpr int WORLD_SIZE = 20;

class Game{
    public:
        Game() :
        window("My awesome game",{800, 800}),
        renderer(window),
        player({128,128}),//Initialize player
        level({WORLD_SIZE,WORLD_SIZE},&player,{2,2},{10,15}, {7,12})//initialize level with set size, pointer to player and start/end grid coordinates
        {
            this->window.setPosition({this->player.getPosition()});
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
        bool menuPage = true;
        gf::View camera;
        
        

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

            Button buttonTest("Button",{700,100},20.0,gf::Color::Cyan, font);
          

            level.addGuard(
				{
            	generateRouteAction(actionType::WAIT,2.0,{1,1}),
            	generateRouteAction(actionType::GO,1.0,{1,1}),
            	generateRouteAction(actionType::WAIT,2.0,{1,1}),
            	generateRouteAction(actionType::GO,1.0,{1,1})

				}
            );
            
        	float dt;
        	
            while (this->window.isOpen()) {

                // homepage display
                if(menuPage == true){
                    
                     // Process events
                    gf::Event event;
                
                    while (this->window.pollEvent(event)) {
                        actions.processEvent(event);
                        this->player.processEvent(event);
                        
                        if(event.type == gf::EventType::MouseButtonPressed){
                        this->startGame();
                        std::cout <<"mouse boutton pressed" << std::endl;
                        menuPage =false;
                    }
                        
                    }
                    if(closeWindowAction.isActive()) {
                        this->window.close();
                    }

                    dt = clock.restart().asSeconds();

                    this->renderer.clear();
                    displayMenuPage();

                    

                    this->renderer.display();
                }else{


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
                        this->win=true;
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


                    //Test button
                    gf::TextButtonWidget aff_button = buttonTest.getButton();
                    this->renderer.draw(aff_button);

                    //if the game is over
                    if(this->isFinished == true){
                        //if he lost
                        if(this->win == false){
                            this->renderer.draw(gameOverText);
                        }else{
                            this->renderer.draw(winText);
                            this->win=false;
                        }
                        this->renderer.draw(pressSpaceText);
                      }

                      //Update and draw View
                      this->viewUpdate();
                      this->renderer.setView(this->camera);

                    
                    this->renderer.display();
                    actions.reset();
                }

            }
            
        }

        void startGame(){
            this->level.reset();
            this->isFinished=false;
        }
        
        void endgame(){
            this->isFinished=true;
        }

        void displayMenuPage(){
            gf::Font font("arial.ttf");

            gf::Text titleText("Steal museum", font); 
            titleText.setCharacterSize(50);
            titleText.setPosition({500,100});
            titleText.setColor(gf::Color::Cyan);
            this->renderer.draw(titleText);

            gf::TextButtonWidget button1 = gf::TextButtonWidget ("Start", font, 30.0);
            button1.setBackgroundOutlineThickness(2);
            button1.setDefaultBackgroundColor(gf::Color::Cyan);
            button1.setPadding(20.0);
            button1.setRadius(12.0);
            button1.setPosition({600,300});

            gf::TextButtonWidget button2 = gf::TextButtonWidget ("Rules", font, 30.0);
            button2.setBackgroundOutlineThickness(2);
            button2.setDefaultBackgroundColor(gf::Color::Cyan);
            button2.setPadding(20.0);
            button2.setRadius(12.0);
            button2.setPosition({600,400});

            gf::TextButtonWidget button3 = gf::TextButtonWidget ("Exit", font,  30.0);
            button3.setBackgroundOutlineThickness(2);
            button3.setDefaultBackgroundColor(gf::Color::Cyan);
            button3.setPadding(20.0);
            button3.setRadius(12.0);
            button3.setPosition({600,500});

            gf::TextButtonWidget aff_button1 = button1;
            this->renderer.draw(aff_button1);

            gf::TextButtonWidget aff_button2 = button2;
            this->renderer.draw(aff_button2);

            gf::TextButtonWidget aff_button3 = button3;
            this->renderer.draw(aff_button3);
        }
        
        void viewUpdate(){
            gf::Vector2f position = this->player.getPosition();
            gf::Vector2f size(500.0, 500.0);
            gf::RectF rect_camera = gf::RectF().fromPositionSize({0,0}, size);
            this->camera.reset(rect_camera);
            this->camera.setCenter(this->player.getPosition());

        }

};

int main() {
  Game game;
  return 0;
}
