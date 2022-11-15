#include <iostream>
#include <gf/Event.h>
#include <gf/Font.h>
#include <gf/RenderWindow.h>
#include <gf/Sprite.h>
#include <gf/Text.h>
#include <gf/Window.h>
#include <gf/Entity.h>
#include <gf/Shapes.h>

 
class Player : public gf::Entity{
    public:
    void onKeyPress(gf::Event e){
        std::cout << "Key press ! \n";
        switch (e.key.keycode){
            case gf::Keycode::Right:
                this->m_velocity = {5,0};
                break;
            case gf::Keycode::Left:
                this->m_velocity = {-5,0};
                break;     
        }
    }
    virtual void update(float dt){
        this->m_position += this->m_velocity  * this->speed * dt;
    }
    virtual void render(gf::RenderTarget& target){
        gf::RectangleShape shape({ 20,20 });
        shape.setPosition(m_position);
        shape.setColor(gf::Color::Black);
        shape.setAnchor(gf::Anchor::Center);
        target.draw(shape);
    };
    private:
    gf::Vector2f m_position; // center of the square
    gf::Vector2f m_velocity;
    double speed;

};

class Game{
    public:    
    Game() : window("My awesome game", { 640, 480 }),renderer(window){        
        this->player = Player();
    }

    void gameloop(){
        this->renderer.clear(gf::Color::White);
        gf::Clock clock;
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
            this->renderer.display();
        }
    }
    private: 
    Player player;
    gf::Window window;
    gf::RenderWindow renderer;
    
};

int main() {

 
 
  Game game;
  game.gameloop();
 
  return 0;
}