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

Camera* GameCore::getCamera() const
    { return camera; }

int GameCore::getNbCharacters() const
    { return characters.size(); }
