cmake_minimum_required(VERSION 3.10)
project(TheLegendOfChrisMinnahl VERSION 0.1.0)

include(GNUInstallDirs)

set(MANAGER_DATA_DIR "${CMAKE_INSTALL_FULL_DATADIR}/games/TheLegendOfChrisMinnahl")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h @ONLY)

find_package(gf REQUIRED)

add_executable(TheLegendOfChrisMinnahl
  main.cc
  manager.cc

  scenes/title.cc
  scenes/rules.cc
  scenes/end.cc
  scenes/game.cc
  scenes/pause.cc
  scenes/mapViewer.cc

  local/player.cc
  local/level.cc
  local/wall.cc
  local/guard.cc
  local/map.cc
  local/minimap.cc
)

target_include_directories(TheLegendOfChrisMinnahl
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(TheLegendOfChrisMinnahl
  PRIVATE
    gf::graphics
)

install(
  TARGETS TheLegendOfChrisMinnahl
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

install(
  DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/data/TheLegendOfChrisMinnahl"
  DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/games"
)