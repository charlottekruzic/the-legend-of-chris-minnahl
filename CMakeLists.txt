cmake_minimum_required(VERSION 3.10)
 
project(Commando
  VERSION 0.1.0
)
 
find_package(gf REQUIRED)
 
add_executable(Commando
  main.cc
  # and the rest of your sources
)
 
target_link_libraries(Commando
  PRIVATE
    gf::graphics
    gf::net
)
