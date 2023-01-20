cmake_minimum_required(VERSION 3.10)
 
project(Commando
  VERSION 0.1.0
)
 
find_package(gf REQUIRED)
find_package(Box2D REQUIRED)


add_executable(Commando
  main.cc
  manager.cc

  scenes/title.cc
  scenes/rules.cc
  scenes/game.cc
  
  local/player.cc
  local/level.cc
  local/wall.cc
  local/guard.cc
  gui/panel.cc
  gui/label.cc
  gui/button.cc
  # and the rest of your sources
)
 
target_link_libraries(Commando
  PRIVATE
    gf::graphics
    gf::net
    Box2D
)
