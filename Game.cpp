//
// Created by lagri on 14.04.2022.
//

#include "Game.h"

void Game::start() {
    RenderWindow window(VideoMode(900, 900), "SFML APP");

    Image charactersImage;
    charactersImage.loadFromFile("EntitiesTexture/characters.png");

    Texture texture;
    texture.loadFromImage(charactersImage);

    AnimationManager heroAM;
    heroAM.loadFromXml("Animation/Hero/anims.xml", texture);

    AnimationManager bigBamboniAM;
    bigBamboniAM.loadFromXml("Animation/BigBamboni/anims.xml", texture);

    AnimationManager smallBamboniAM;
    smallBamboniAM.loadFromXml("Animation/SmallBamboni/anims.xml", texture);

    // Инициализация уровня
    Level level;
    level.loadFromXmlFile("Levels/level1/level.tmx");

    // Инициализация фабрики
    EntityFactory factory(level);

    // Инициализация главного героя
    Object heroObj = level.getObject("hero");
    auto *hero = new HeroEntity(heroAM, level, heroObj.rect.left, heroObj.rect.top);

    vector<Entity *> entities;
    initEnemies(entities, bigBamboniAM, smallBamboniAM, level, factory);

    // Инициализация блока для активации
    // окончания игры
    const Object &endBlock = level.getObject("end");

    const Object &key = level.getObject("key");

    Clock clock;
    float time;

    cout << "Game ran" << endl;
    while (window.isOpen()) {
        window.clear();

        updateTime(clock, time);

        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
        }

        // Не трогать эту строку
        level.draw(window);

        setPressedKeyset(hero);

        handleEntityInteraction(window, hero, entities, time, endBlock, key);

        hero->update(time);
        hero->draw(window);

        window.display();
    }

    cout << "Game stopped" << endl;

    exit(0);
}

/* Обновление времени для отрисовки и обработки игры */
void Game::updateTime(Clock &clock, float &time) {
    time = clock.getElapsedTime().asMicroseconds();
    clock.restart();
    time /= 650;
    if (time > 60) time = 60;
}

/* Инициализация противников через фабрику,
 * считывая их изначальное расположение на карте */
void Game::initEnemies(vector<Entity *> &entities, AnimationManager &bigBamboniAM, AnimationManager &smallBamboniAM,
                       Level &level, EntityFactory &factory) {
    for (const auto &enemy: level.getObjects("enemy")) {
        if (enemy.type == "big_bamboni") {
            entities.push_back(
                    factory.getEntity(
                            EntityFactory::BIGBAMBONI, bigBamboniAM, enemy.rect.left, enemy.rect.top
                    )
            );
        } else if (enemy.type == "small_bamboni") {
            entities.push_back(
                    factory.getEntity(
                            EntityFactory::SMALLBAMBONI, smallBamboniAM, enemy.rect.left, enemy.rect.top
                    )
            );
        }
    }
}

/* Обработка взаимодействия персонажа с различными сущностями */
void Game::handleEntityInteraction(RenderWindow &window, HeroEntity *hero, vector<Entity *> &entities,
                                   float time, const Object &endBlock, const Object &key) {
    for (auto &entity: entities) {
        if (entity->getObjName() == "enemy") {

            if (entity->getHealth() <= 0) continue;

            if (hero->getRect().intersects(entity->getRect())) {

                if (hero->getDy() > 0.0) {

                    entity->setDx(0.0);
                    hero->setDy(-0.2);

                    entity->setHealth(entity->getHealth() - 1);

                } else if (!hero->isHit()) {

                    hero->setHealth(hero->getHealth() - 1);

                    hero->setIsHit(true);

                    hero->setX(
                            hero->getCurrentMoveDir() == RIGHT
                            ? hero->getX() + 5
                            : hero->getX() - 5
                    );
                }
            }
        }

        entity->update(time);
        entity->draw(window);
    }

    if (hero->isHasKey()) {
        Font f;
        f.loadFromFile("AGENCYB.TTF");
        Text text("Key: +", f, 24);
        text.setPosition(30, 50);
        window.draw(text);

        if (hero->getRect().intersects(endBlock.rect)) {
            cout << "Level passed!!!" << "Congrats!" << endl;
            exit(0);
        }
    }

    if (hero->getRect().intersects(key.rect)) {
        hero->setHasKey(true);
    }
}

void Game::setPressedKeyset(HeroEntity *hero) {
    if (Keyboard::isKeyPressed(Keyboard::W)) hero->setKeyValue("W", true);
    if (Keyboard::isKeyPressed(Keyboard::A)) hero->setKeyValue("A", true);
    if (Keyboard::isKeyPressed(Keyboard::S)) hero->setKeyValue("S", true);
    if (Keyboard::isKeyPressed(Keyboard::D)) hero->setKeyValue("D", true);
}