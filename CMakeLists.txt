cmake_minimum_required(VERSION 3.21)
project(sfmltrain)

set(CMAKE_CXX_STANDARD 17)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/Programs/SFML/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML 2.5 COMPONENTS system window graphics audio network REQUIRED)
include_directories(C:/Programs/SFML/SFML-2.5.1/include)

add_executable(sfmltrain main.cpp Hero.cpp Hero.h Camera.cpp Camera.h Animation.cpp Animation.h AnimationManager.cpp AnimationManager.h)

target_link_libraries(sfmltrain sfml-graphics sfml-audio)
