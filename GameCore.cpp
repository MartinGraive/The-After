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

GameCore::GameCore() : clockStopped(false), clockValueStopped(0)
{
    clock.restart();
}

GameCore::~GameCore()
{
    TextureHandler::getInstance()->freeGame();
    delete entities;
    delete map;
    delete hud;
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
    hud = new HUD;
    //if no window given in argument: no drawing intended, this is a test situation and thus camera is useless
    if (window != NULL) camera = new Camera(window);

    entities = new RenderingArray;
    mplayer = new MainPlayer(TextureHandler::getInstance()->getVigils(0), entities);
    mplayer->setXtile(52);
    mplayer->setYtile(61,false);
    entities->addEntity(mplayer);
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

HUD* GameCore::getHUD() const
    { return hud; }

int GameCore::getNbCharacters() const
    { return characters.size(); }

sf::Int32 GameCore::getElapsedTime() const
{
    if (!clockStopped) return clock.getElapsedTime().asMilliseconds();
    else return clockValueStopped;
}

void GameCore::stopTime()
    { clockStopped = true; clockValueStopped = clock.getElapsedTime().asMilliseconds(); }
