//
// Created by lagri on 14.04.2022.
//

#include "Game.h"

void Game::start() {
    RenderWindow window(VideoMode(900, 900), "SFML APP");

    Image charactersImage;
    charactersImage.loadFromFile("EntitiesTexture/characters.png");

    Image tilesImage;
    tilesImage.loadFromFile("EntitiesTexture/tiles.png");

    Texture charactersTexture;
    charactersTexture.loadFromImage(charactersImage);

    Texture tilesTexture;
    tilesTexture.loadFromImage(tilesImage);

    AnimationManager heroAM;
    heroAM.loadFromXml("Animation/Hero/anims.xml", charactersTexture);

    AnimationManager bigBamboniAM;
    bigBamboniAM.loadFromXml("Animation/BigBamboni/anims.xml", charactersTexture);

    AnimationManager smallBamboniAM;
    smallBamboniAM.loadFromXml("Animation/SmallBamboni/anims.xml", charactersTexture);

    AnimationManager coinAM;
    coinAM.loadFromXml("Animation/Coin/anims.xml", tilesTexture);

    AnimationManager padlockAM;
    padlockAM.loadFromXml("Animation/Padlock/anims.xml", tilesTexture);

    AnimationManager keyAM;
    keyAM.loadFromXml("Animation/Key/anims.xml", tilesTexture);

    // Инициализация уровня
    Level level;
    level.loadFromXmlFile("Levels/level1/level.tmx");

    // Инициализация фабрики двигающихся сущностей
    EntityFactory entityFactory(level);

    // Инициализация фабрики предметов
    SubjectFactory subjectFactory(level);

    // Инициализация главного героя
    Object heroObj = level.getObject("hero");
    auto *hero = new HeroEntity(heroAM, level, heroObj.rect.left, heroObj.rect.top);

    vector<Subject *> subjects;
    initSubjects(coinAM, padlockAM, keyAM, level, subjectFactory, subjects);

    vector<Entity *> entities;
    initEnemies(entities, bigBamboniAM, smallBamboniAM, level, entityFactory);

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

        handleEntities(window, hero, entities, time);

        handleSubjects(window, hero, subjects, time);

        hero->update(time);
        hero->draw(window);

        window.display();
    }

    cout << "Game stopped" << endl;

    exit(0);
}

void Game::initSubjects(AnimationManager &coinAM, AnimationManager &padlockAM, AnimationManager &keyAM, Level &level,
                        SubjectFactory &subjectFactory, vector<Subject *> &subjects) {
    for (const auto &subject: level.getObjects("subject")) {
        if (subject.type == "coin") {
            subjects.push_back(
                    subjectFactory.getSubject(SubjectFactory::COIN, coinAM, subject.rect.left, subject.rect.top)
            );
        } else if (subject.type == "padlock") {
            subjects.push_back(
                    subjectFactory.getSubject(SubjectFactory::PADLOCK, padlockAM, subject.rect.left, subject.rect.top)
            );
        } else if (subject.type == "key") {
            subjects.push_back(
                    subjectFactory.getSubject(SubjectFactory::KEY, keyAM, subject.rect.left, subject.rect.top)
            );
        }
    }
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

/* Обновление предметов */
void Game::handleSubjects(RenderWindow &window, HeroEntity *hero, vector<Subject *> &subjects, float time) {
    for (auto &subject: subjects) {
        if (subject->getObjName() == "coin") {
            if (hero->getRect().intersects(subject->getRect())) {
                hero->setCoins(hero->getCoins() + 1);
            }
        } else if (subject->getObjName() == "padlock") {
            if (hero->getRect().intersects(subject->getRect()) && hero->isHasKey()) {
                cout << "Level passed!";
                exit(228);
            }
        } else if (subject->getObjName() == "key") {
            if (hero->getRect().intersects(subject->getRect())) {
                hero->setHasKey(true);
            }
        }

        subject->update(time);
        subject->draw(window);
    }
};

/* Обновление сущностей */
void Game::handleEntities(RenderWindow &window, HeroEntity *hero, vector<Entity *> &entities, float time) {
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
    }
}

void Game::setPressedKeyset(HeroEntity *hero) {
    if (Keyboard::isKeyPressed(Keyboard::W)) hero->setKeyValue("W", true);
    if (Keyboard::isKeyPressed(Keyboard::A)) hero->setKeyValue("A", true);
    if (Keyboard::isKeyPressed(Keyboard::S)) hero->setKeyValue("S", true);
    if (Keyboard::isKeyPressed(Keyboard::D)) hero->setKeyValue("D", true);
}