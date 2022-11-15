 
#include <gf/Event.h>
#include <gf/Font.h>
#include <gf/RenderWindow.h>
#include <gf/Sprite.h>
#include <gf/Text.h>
#include <gf/Window.h>
 
int main() {
  // Create the main window and the renderer
 
  gf::Window window("Example", { 640, 480 });
  gf::RenderWindow renderer(window);
 
 
  renderer.clear(gf::Color::White);
 
  // Start the game loop
 
  while (window.isOpen()) {
 
    // Process events
 
    gf::Event event;
 
    while (window.pollEvent(event)) {
      switch (event.type) {
        case gf::EventType::Closed:
          window.close();
          break;
 
        default:
          break;
      }
    }
 
    // Draw the entities
 
    renderer.clear();
    renderer.display();
  }
 
  return 0;
}