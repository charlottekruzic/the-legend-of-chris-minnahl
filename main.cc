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
#include <gf/WidgetContainer.h>
#include <gf/Widgets.h>
#include <Box2D/Box2D.h>
//Include local headers
#include "local/player.h"
#include "local/level.h"
#include "local/guard.h"
#include "gui/panel.h"
#include "gui/label.h"
#include "gui/button.h"


constexpr int WORLD_SIZE = 20;
constexpr gf::Vector2f WINDOW_SIZE = {800.0, 800.0};

class Game{
    public:
        Game() :
        window("My awesome game",WINDOW_SIZE),
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
        	this->level.addWall({6,6});
        	this->level.addWall({1,10});
        	this->level.addWall({18,19});
        	this->level.addWall({17,19});
        	this->level.addWall({16,19});


            //Création du menu
            gf::Font font("arial.ttf");

            this->titleText = gf::Text("Steal museum", font); 
            this->titleText.setCharacterSize(50);
            this->titleText.setPosition({300.0,100.0});
            this->titleText.setColor(gf::Color::Cyan);

            gf::TextButtonWidget button1("Start", font, 30.0);
            button1.setPosition({WINDOW_SIZE[0]/2 ,300.0});
            gf::TextButtonWidget button2("Rules", font, 30.0);
            button2.setPosition({WINDOW_SIZE[0]/2,400.0});
            gf::TextButtonWidget button3("Exit", font,  30.0);
            button3.setPosition({WINDOW_SIZE[0]/2,500.0});

            this->buttons.push_back(button1);
            this->buttons.push_back(button2);
            this->buttons.push_back(button3);

            for(int i=0;i<this->buttons.size();i++){
                this->buttons[i].setBackgroundOutlineThickness(2);
                this->buttons[i].setDefaultBackgroundColor(gf::Color::Cyan);
                this->buttons[i].setPadding(20.0);
                this->buttons[i].setRadius(12.0);
            }
            
            
            this->gameloop();
        }

    private: 
        Player player;
        gf::Window window;
        gf::RenderWindow renderer;
        Level level;
        bool isFinished;
        bool win;
        bool menuPage = true;
        gf::View camera;
        std::vector<gf::TextButtonWidget> buttons;
        gf::Text titleText; 
        
        
        void startGame(){
            this->level.reset();
            this->isFinished=false;
        }
        
        void endgame(){
            this->isFinished=true;
        }
        
        void viewUpdate(){
            if(this->menuPage || this->isFinished){
                gf::RectF rect_camera = gf::RectF().fromPositionSize({0,0}, WINDOW_SIZE);
                this->camera.reset(rect_camera);
            }else{
                gf::Vector2f position = this->player.getPosition();
                gf::Vector2f size(500.0, 500.0);
                gf::RectF rect_camera = gf::RectF().fromPositionSize({0,0}, size);
                this->camera.reset(rect_camera);
                this->camera.setCenter(this->player.getPosition());
            }
            this->renderer.setView(this->camera);
        }

        
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
            gameOverText.setCharacterSize(60);
            gameOverText.setPosition({(WINDOW_SIZE[0]/2)-60,WINDOW_SIZE[1]/2});
            gameOverText.setColor(gf::Color::Red);
            
            winText.setCharacterSize(60);
            winText.setPosition({(WINDOW_SIZE[0]/2)-60,WINDOW_SIZE[1]/2});
            winText.setColor(gf::Color::Red);
            
            pressSpaceText.setCharacterSize(25);
            pressSpaceText.setPosition({(WINDOW_SIZE[0]/2)-140,(WINDOW_SIZE[1]/2)+20});
            pressSpaceText.setColor(gf::Color::Red);

            Button buttonTest("Button",{700,100},20.0,gf::Color::Cyan, font);
          

            level.addGuard( 
            	{15,1},
				{
            	generateRouteAction(actionType::GO		,1.0,{8,1}),
            	generateRouteAction(actionType::WAIT	,2.0,{0,0}),
            	generateRouteAction(actionType::GO		,1.0,{8,5}),
            	generateRouteAction(actionType::WAIT	,1.0,{0,0}),
            	generateRouteAction(actionType::GO		,1.0,{8,1}),
            	generateRouteAction(actionType::WAIT	,2.0,{0,0}),
            	generateRouteAction(actionType::GO		,1.0,{15,1}),
            	generateRouteAction(actionType::WAIT	,1.0,{0,0})


				}
            );
            level.addGuard(
            	{5,18},
				{
            	generateRouteAction(actionType::GO		,1.0,{15,18}),
            	generateRouteAction(actionType::WAIT	,2.0,{0,0}),
            	generateRouteAction(actionType::GO		,1.0,{15,10}),
            	generateRouteAction(actionType::WAIT	,1.0,{0,0}),
            	generateRouteAction(actionType::GO		,1.0,{5,10}),
            	generateRouteAction(actionType::WAIT	,2.0,{0,0}),
            	generateRouteAction(actionType::GO		,1.0,{5,18}),
            	generateRouteAction(actionType::WAIT	,1.0,{0,0})


				}
            );            
        	float dt;
        	
            while (this->window.isOpen()) {
                dt = clock.restart().asSeconds();

                // homepage display
                if(menuPage == true){
                    
                    // Process events
                    gf::Event event;

                    if(closeWindowAction.isActive()) {
                        this->window.close();
                    }

                    while (this->window.pollEvent(event)) {
                        gf::MouseButtonEvent &mouseEvent = event.mouseButton;
                        switch (event.type) {
                            case gf::EventType::MouseButtonPressed:
                                for(int i=0;i<this->buttons.size();i++){
                                    if(this->buttons[i].contains(mouseEvent.coords)){
                                        this->buttons[i].setSelected();
                                    }
                                }
                                break;
                            case gf::EventType::MouseButtonReleased:
                                for(int i=0;i<this->buttons.size();i++){
                                    this->buttons[i].setState(gf::WidgetState::Default );
                                }
                                if(this->buttons[0].contains(mouseEvent.coords)){
                                    this->startGame();
                                    menuPage =false;
                                }else if(this->buttons[1].contains(mouseEvent.coords)){

                                }else if(this->buttons[2].contains(mouseEvent.coords)){
                                    this->window.close();
                                }
                                break;

                            default:
                                break;
                        }
                    }                 

                    this->renderer.clear();

                    //Affichage éléments de l'écran d'accueil
                    this->renderer.draw(this->titleText);
                    for(int i=0;i<this->buttons.size();i++){
                        this->renderer.draw(this->buttons[i]);
                    }
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
                    }else if(level.isLoose()){
                    	this->win=false;
                        this->endgame();
                    }

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
                    // gf::TextButtonWidget aff_button = buttonTest.getButton();
                    // this->renderer.draw(aff_button);

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
                    this->renderer.display();
                    
                    actions.reset();
                }

            }
            
        }



};

int main() {
  Game game;
  return 0;
}
