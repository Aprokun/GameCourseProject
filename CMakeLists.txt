cmake_minimum_required(VERSION 3.21)
project(sfmltrain)

set(CMAKE_CXX_STANDARD 17)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/Programs/SFML/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML 2.5 COMPONENTS system window graphics audio network REQUIRED)
include_directories(C:/Programs/SFML/SFML-2.5.1/include)

add_executable(
        sfmltrain
        main.cpp
        TinyXML2/tinyxml2.h
        TinyXML2/tinyxml2.cpp
        Entities/HeroEntity.cpp
        Entities/HeroEntity.h
        Camera.cpp
        Camera.h
        Animation/Animation.cpp
        Animation/Animation.h
        Animation/AnimationManager.cpp
        Animation/AnimationManager.h
        Entities/Entity.cpp
        Entities/Entity.h
        Factories/EntityFactory.cpp
        Factories/EntityFactory.h
        Entities/SmallBamboni.cpp
        Entities/SmallBamboni.h
        Entities/BigBamboni.cpp
        Entities/BigBamboni.h
        Level/Level.cpp
        Level/Level.h
        Game.cpp
        Game.h
        Subjects/Subject.cpp
        Subjects/Subject.h
        Subjects/Coin.cpp
        Subjects/Coin.h
        Factories/SubjectFactory.cpp
        Factories/SubjectFactory.h
        Subjects/Key.cpp
        Subjects/Key.h
        Subjects/Padlock.cpp
        Subjects/Padlock.h)

target_link_libraries(sfmltrain sfml-graphics sfml-audio)
