$cmake_minimum_required(VERSION 3.10)

set(MANAGER_DATA_DIR "${CMAKE_INSTALL_PREFIX}/share/games/Commando")               
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h @ONLY)

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
  scenes/end.cc
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

target_include_directories(Commando
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(Commando
  PRIVATE
    gf::graphics
    gf::net
    Box2D
)

install(
  TARGETS Commando
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

install(
  DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/data"
  DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}"
)

