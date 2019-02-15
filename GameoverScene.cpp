/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include "GameoverScene.h"
#include "GameCore.h"
#include "Graphics/TextureHandler.h"
#include "Graphics/Graphics.h"
#include "SceneManager.h"
#include "Camera.h"

GameoverScene::GameoverScene(sf::RenderWindow* win) : frameElapsed(0), window(win)
{
}

void GameoverScene::draw()
{
    GameCore* gameCore = GameCore::getInstance();

    gameCore->getMap()->drawFloor(window);

    drawEntities();

    gameCore->getMap()->drawCeil(window);

    drawAboveEntities();

    Texture tex = TextureHandler::getInstance()->getWeisted();
    MainPlayer* m = GameCore::getInstance()->getMPlayer();
    int posx = - tex.w / 2 + m->getXbase() + m->getBaseRect().w / 2;
    int posy = - tex.h / 2 + m->getYbase() + m->getBaseRect().h / 2;
    Graphics::getInstance()->drawSprite(window, tex,
                         posx, posy);
}

void GameoverScene::process()
{
    frameElapsed++;

    if (frameElapsed > 500) {
        GameCore::getInstance()->getCamera()->reset();
        SceneManager::getInstance()->popScene();
        SceneManager::getInstance()->popScene();
    }
}

void GameoverScene::drawEntities()
{
    GameCore* gameCore = GameCore::getInstance();

    for (int i = 0 ; i<gameCore->getEntities()->size() ; i++) {
        gameCore->getEntities()->getEntity(i)->draw(window);
    }
}

void GameoverScene::drawAboveEntities()
{
    GameCore* gameCore = GameCore::getInstance();

    for (int i = 0 ; i<gameCore->getEntities()->size() ; i++) {
        gameCore->getEntities()->getEntity(i)->drawAbove(window);
    }

    gameCore->getHUD()->draw(window);
}

int GameoverScene::getType()
    { return GAMEOVER; }

