/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include "GameCore.h"
#include "Graphics/TextureHandler.h"
#include "Student.h"

GameCore* GameCore::instance = NULL;

GameCore::GameCore()
{
}

GameCore::~GameCore()
{
    TextureHandler::getInstance()->freeGame();
    delete entities;
    delete map;
    delete camera;
}

GameCore* GameCore::getInstance() { return instance; }

void GameCore::createInstance(sf::RenderWindow* window)
{
    instance = new GameCore;
    instance->init(window);
}

void GameCore::init(sf::RenderWindow* window)
{
    TextureHandler::getInstance()->loadGame();

    map = new Map;
    map->loadMap(1);
    //if no window given in argument: no drawing intended, this is a test situation and thus camera is useless
    if (window != NULL) camera = new Camera(window);

    entities = new RenderingArray;
    mplayer = new MainPlayer(TextureHandler::getInstance()->getVigils(0), entities);
    mplayer->setX(180);
    mplayer->setY(180, false);
    entities->addEntity(mplayer);

    Student* student = new Student(TextureHandler::getInstance()->getCharas(0), entities);
    student->setX(400);
    student->setY(180, false);
    addCharacter(student);

    Student* student2 = new Student(TextureHandler::getInstance()->getCharas(0), entities);
    student2->setX(500);
    student2->setY(200, false);
    addCharacter(student2);

    Student* student3 = new Student(TextureHandler::getInstance()->getCharas(0), entities);
    student3->setX(520);
    student3->setY(230, false);
    addCharacter(student3);
}

RenderingArray* GameCore::getEntities() const
    { return entities; }

Map* GameCore::getMap() const
    { return map; }

MainPlayer* GameCore::getMPlayer() const
    { return mplayer; }

Character* GameCore::getCharacters(int i) const
    { return characters[i]; }

void GameCore::addCharacter(Character* i)
{
    characters.push_back(i);
    entities->addEntity(i);
}

void GameCore::removeCharacter(Character* c)
{
    int num = -1;
    for (unsigned int i = 0 ; i < characters.size() ; i++) {
        if (characters[i] == c) { num = i; break; }
    }
    if (num > -1) {
        entities->removeEntity(c);
        for (unsigned int i = num ; i < characters.size() - 1 ; i++) { characters[i] = characters[i + 1]; }
        characters.pop_back();
    }
}

Camera* GameCore::getCamera() const
    { return camera; }

int GameCore::getNbCharacters() const
    { return characters.size(); }
