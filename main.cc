#include <iostream>
#include <fstream>
#include <string>
#include <gf/Event.h>
#include <gf/Font.h>
#include <gf/RenderWindow.h>
#include <gf/Sprite.h>
#include <gf/Text.h>
#include <gf/Window.h>
#include <gf/Entity.h>
#include <gf/Shapes.h>
#include <gf/ViewContainer.h>
#include <gf/View.h>
#include <gf/Views.h>
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

constexpr gf::Vector2f WINDOW_SIZE = {800.0, 800.0};
constexpr gf::Vector2f GAME_SIZE = {500.0, 500.0};


class Game{
    public:
        Game() :
        window("The Legend Of Chris Minnahl",WINDOW_SIZE),
        renderer(window),
        player({128,128}),//Initialize player
        level(&player,"levels/2.txt")//initialize level with set size, pointer to player and start/end grid coordinates
        {
            this->window.setPosition({this->player.getPosition()});
            this->isFinished = false;
            this->win = false;

            //Ajout des vues
            this->mainView = gf::FitView(gf::RectF::fromPositionSize({0.0f, 0.0f}, WINDOW_SIZE));
            views.addView(this->mainView);

            this->gameView = gf::FitView(gf::RectF::fromPositionSize({0.0f, 0.0f}, GAME_SIZE));
            views.addView(this->gameView);

            this->minimap = gf::FitView(gf::RectF::fromPositionSize({-WINDOW_SIZE[0]*3, 0.0}, WINDOW_SIZE*4));
            views.addView(this->minimap);

            views.setInitialFramebufferSize(WINDOW_SIZE);
            

            //Création du menu
            gf::Font font("arial.ttf");

            this->titleMenu = gf::Text("The Legend Of Chris Minnahl", font);
            this->titleMenu.setCharacterSize(50);
            this->titleMenu.setAnchor(gf::Anchor::Center);
            this->titleMenu.setPosition({WINDOW_SIZE[0]/2,100.0});
            this->titleMenu.setColor(gf::Color::Cyan);

            gf::TextButtonWidget button1("Start", font, 30.0);
            button1.setAnchor(gf::Anchor::Center);
            button1.setPosition({WINDOW_SIZE[0]/2 ,300.0});
            gf::TextButtonWidget button2("Rules", font, 30.0);
            button2.setAnchor(gf::Anchor::Center);
            button2.setPosition({WINDOW_SIZE[0]/2,400.0});
            gf::TextButtonWidget button3("Exit", font,  30.0);
            button3.setAnchor(gf::Anchor::Center);
            button3.setPosition({WINDOW_SIZE[0]/2,500.0});

            this->buttons.push_back(button1);
            this->buttons.push_back(button2);
            this->buttons.push_back(button3);

            for(int i=0;i<3;i++){
                this->buttons[i].setBackgroundOutlineThickness(2);
                this->buttons[i].setDefaultBackgroundColor(gf::Color::Cyan);
                this->buttons[i].setPadding(20.0);
                this->buttons[i].setRadius(12.0);
            }

            //Création page règles du jeu
            this->titleRules = gf::Text("The game's rules", font); 
            this->titleRules.setCharacterSize(50);
            this->titleRules.setAnchor(gf::Anchor::Center);
            this->titleRules.setPosition({WINDOW_SIZE[0]/2,100.0});
            this->titleRules.setColor(gf::Color::White);

            gf::TextButtonWidget button4("Return", font, 20.0);
            button4.setAnchor(gf::Anchor::TopRight);
            button4.setPosition({WINDOW_SIZE[0]-30 ,30.0});
            button4.setBackgroundOutlineThickness(2);
            button4.setDefaultBackgroundColor(gf::Color::White);
            button4.setPadding(10.0);
            button4.setRadius(12.0);
            this->buttons.push_back(button4);


            std::ifstream rulesFile ("local/game_rules.txt");
            std::string rules;

            if (rulesFile.is_open()) {
                while (rulesFile) {
                std::string line;
                    std::getline (rulesFile, line);
                    rules+=line+"\n";
                }
            }else {
                std::cout << "Couldn't open file\n";
            }

            this->gameRules.setString(rules);
            this->gameRules.setFont(font);
            this->gameRules.setParagraphWidth(WINDOW_SIZE[0]-WINDOW_SIZE[0]/8);
            this->gameRules.setAlignment(gf::Alignment::Left);
            this->gameRules.setCharacterSize(20);
            this->gameRules.setAnchor(gf::Anchor::Center);
            this->gameRules.setPosition({WINDOW_SIZE[0]/2,WINDOW_SIZE[1]/2});
            this->gameRules.setColor(gf::Color::White);


            //Page jeu
            gf::TextButtonWidget button5("Menu", font, 20.0);
            button5.setAnchor(gf::Anchor::TopRight);
            button5.setPosition({WINDOW_SIZE[0]-WINDOW_SIZE[1]/25 ,30.0});
            button5.setBackgroundOutlineThickness(2);
            button5.setDefaultBackgroundColor(gf::Color::White);
            button5.setPadding(10.0);
            button5.setRadius(12.0);
            this->buttons.push_back(button5);
            
            this->gameloop();
        }

    private: 
        gf::Window window;
        gf::RenderWindow renderer;
        Player player;
        Level level;
        bool isFinished;
        bool win;
        bool menuPage = true;
        bool rulesPage = false;
        gf::ViewContainer views;
        gf::FitView mainView;
        gf::FitView gameView;
        gf::FitView minimap;
        std::vector<gf::TextButtonWidget> buttons;
        gf::Text titleMenu; 
        gf::Text titleRules; 
        gf::Text gameRules;
        
        
        
        void startGame(){
            this->level.reset();
            this->isFinished=false;
        }
        
        void endgame(){
            this->isFinished=true;
        }
        
        void viewUpdate(){
            if(this->menuPage || this->isFinished){
                this->renderer.setView(this->mainView);
            }else{
                this->gameView.reset(gf::RectF().fromPositionSize({0,0}, GAME_SIZE));
                this->gameView.setCenter(this->player.getPosition());
                this->renderer.setView(this->gameView);
            }
        }

        
        void gameloop(){

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
            gameOverText.setAnchor(gf::Anchor::Center);
            gameOverText.setPosition({WINDOW_SIZE[0]/2,(WINDOW_SIZE[1]/2)-(WINDOW_SIZE[1]/32)});
            gameOverText.setColor(gf::Color::Red);
            
            winText.setCharacterSize(60);
            winText.setAnchor(gf::Anchor::Center);
            winText.setPosition({WINDOW_SIZE[0]/2,(WINDOW_SIZE[1]/2)-(WINDOW_SIZE[1]/32)});
            winText.setColor(gf::Color::Red);
            
            pressSpaceText.setCharacterSize(25);
            pressSpaceText.setAnchor(gf::Anchor::Center);
            pressSpaceText.setPosition({WINDOW_SIZE[0]/2,(WINDOW_SIZE[1]/2)+(WINDOW_SIZE[1]/32)});
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
        
                // homepage display
                if(menuPage){
                    
                    gf::Event event;     

                    while (this->window.pollEvent(event)) {
                        actions.processEvent(event);
                        views.processEvent(event);

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
                                    rulesPage = true;
                                    menuPage = false;
                                }else if(this->buttons[2].contains(mouseEvent.coords)){
                                    this->window.close();
                                }
                                break;

                            default:
                                break;
                        }
                    }   

                    if(closeWindowAction.isActive()) {
                        this->window.close();
                    }              

                    this->renderer.clear();
                    this->renderer.clear(gf::Color::Gray(0.3));

                    //Affichage éléments de l'écran d'accueil
                    this->renderer.draw(this->titleMenu);
                    for(int i=0;i<3;i++){
                        this->renderer.draw(this->buttons[i]);
                    }
                    this->renderer.display();

                    actions.reset();

                }else if(rulesPage) {
                    gf::Event event;

                    while (this->window.pollEvent(event)) {
                        actions.processEvent(event);
                        views.processEvent(event);

                        gf::MouseButtonEvent &mouseEvent = event.mouseButton;
                        switch (event.type) {
                            case gf::EventType::MouseButtonPressed:
                                if(this->buttons[3].contains(mouseEvent.coords)){
                                        this->buttons[3].setSelected();
                                }
                                break;
                            case gf::EventType::MouseButtonReleased:
                                this->buttons[3].setState(gf::WidgetState::Default );

                                if(this->buttons[3].contains(mouseEvent.coords)){
                                    rulesPage = false;
                                    menuPage = true;
                                }
                                break;
                            default:
                                break;
                        }
                    }
                    
                    if(closeWindowAction.isActive()) {
                        this->window.close();
                    } 


                    this->renderer.clear(); 

                    this->renderer.draw(this->titleRules);
                    this->renderer.draw(this->buttons[3]);
                    this->renderer.draw(this->gameRules);

                    this->renderer.display();

                    actions.reset();

                }else{
                    //Update and draw View

                    gf::Event event;

                    while (this->window.pollEvent(event)) {
                        actions.processEvent(event);
                        views.processEvent(event);
                        this->player.processEvent(event);

                        gf::MouseButtonEvent &mouseEvent = event.mouseButton;
                        switch (event.type) {
                            case gf::EventType::MouseButtonPressed:
                                if(this->buttons[4].contains(mouseEvent.coords)){
                                        this->buttons[4].setSelected();
                                }
                                break;
                            case gf::EventType::MouseButtonReleased:
                                this->buttons[4].setState(gf::WidgetState::Default);
                                if(this->buttons[4].contains(mouseEvent.coords)){
                                    menuPage = true;
                                }
                                break;
                            default:
                                break;
                        }
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

                    dt = clock.restart().asSeconds();

                    if(isFinished == false){
                        //Update
                        this->player.update(dt);
                        this->level.update(dt);
                    }

                    // Draw the entities
                    this->renderer.clear();
                    
                    this->viewUpdate();

                    this->level.render(this->renderer, false);
                    this->player.render(this->renderer);
                    this->level.renderScore(this->renderer, GAME_SIZE);

                    if(isFinished){
                        this->renderer.draw(this->buttons[4]);
                    }                

                    //Affichage minimap
                    if(!isFinished){
                        this->renderer.setView(this->minimap);
                        this->level.render(this->renderer, true);
                        this->player.render(this->renderer);
                    }


                    //if the game is over
                    if(isFinished == true){
                        //if he lost
                        if(this->win == false){
                            this->renderer.draw(gameOverText);
                        }else{
                            this->renderer.draw(winText);
                            this->win=false;
                        }
                        this->renderer.draw(pressSpaceText);
                    }
                    

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
