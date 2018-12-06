/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include "GameScene.h"
#include "GameCore.h"
#include "Graphics/TextureHandler.h"

GameScene::GameScene(sf::RenderWindow* win) : window(win)
{
    GameCore::createInstance(window);
}

void GameScene::draw()
{
    GameCore* gameCore = GameCore::getInstance();

    gameCore->getMap()->drawFloor(window);

    drawEntities();

    gameCore->getMap()->drawCeil(window);

    drawAboveEntities();
}

void GameScene::process()
{
    GameCore* gameCore = GameCore::getInstance();
    gameCore->getCamera()->autoScroll();

    for (int i = 0 ; i < gameCore->getEntities()->size() ; i++) {
        gameCore->getEntities()->getEntity(i)->process();
    }
}

void GameScene::drawEntities()
{
    GameCore* gameCore = GameCore::getInstance();

    for (int i = 0 ; i<gameCore->getEntities()->size() ; i++) {
        gameCore->getEntities()->getEntity(i)->draw(window);
    }
}

void GameScene::drawAboveEntities()
{
    GameCore* gameCore = GameCore::getInstance();

    for (int i = 0 ; i<gameCore->getEntities()->size() ; i++) {
        gameCore->getEntities()->getEntity(i)->drawAbove(window);
    }
}
