/*THE AFTER
Commenc� le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include "GameCore.h"
#include "Graphics/TextureHandler.h"
#include "Vigil.h"

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
    map = new Map;
    map->loadMap(1);
    camera = new Camera(window);

    TextureHandler::getInstance()->loadGame();
    entities = new RenderingArray;
    mplayer = new MainPlayer(TextureHandler::getInstance()->getCharas(0), entities);
    mplayer->setX(180);
    mplayer->setY(180, false);
    entities->addEntity(mplayer);

    Vigil* gaspard = new Vigil(TextureHandler::getInstance()->getVigils(0), entities);
    gaspard->setX(400);
    gaspard->setY(180, false);
    addCharacter(gaspard);
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
