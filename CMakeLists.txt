cmake_minimum_required(VERSION 3.21)
project(sfmltrain)

set(CMAKE_CXX_STANDARD 17)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/Programs/SFML/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML 2.5 COMPONENTS system window graphics audio network REQUIRED)
include_directories(C:/Programs/SFML/SFML-2.5.1/include)

add_executable(sfmltrain
        main.cpp
        TinyXML/tinystr.h
        TinyXML/tinystr.cpp
        TinyXML/tinyxml.h
        TinyXML/tinyxml.cpp
        TinyXML/tinyxmlerror.cpp
        TinyXML/tinyxmlparser.cpp
        TinyXML2/tinyxml2.h
        TinyXML2/tinyxml2.cpp
        Entities/HeroEntity.cpp
        Entities/HeroEntity.h
        Camera.cpp
        Camera.h
        Animation.cpp
        Animation.h
        AnimationManager.cpp
        AnimationManager.h
        Entities/Entity.cpp
        Entities/Entity.h
        EntityFactory.cpp
        EntityFactory.h
        Entities/ZombieEntity.cpp
        Entities/ZombieEntity.h
        Entities/SlimeEntity.cpp
        Entities/SlimeEntity.h
        Level.cpp
        Level.h
        )

target_link_libraries(sfmltrain sfml-graphics sfml-audio)
