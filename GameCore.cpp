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
    mplayer = new MainPlayer(entities);
    mplayer->setX(180);
    mplayer->setY(180, false);
    entities->addEntity(mplayer);
}

RenderingArray* GameCore::getEntities() const
    { return entities; }

Map* GameCore::getMap() const
    { return map; }

MainPlayer* GameCore::getMPlayer() const
    { return mplayer; }

Camera* GameCore::getCamera() const
    { return camera; }
