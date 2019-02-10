/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include "TitleScene.h"
#include "GameCore.h"
#include "Graphics/TextureHandler.h"
#include "Graphics/Graphics.h"
#include "GameScene.h"

TitleScene::TitleScene(sf::RenderWindow* win) : window(win)
{
    title = TextureHandler::getInstance()->loadTexture(Settings::getInstance()->getPath()+"data/graphics/title/title.png");
}

TitleScene::~TitleScene()
{
    delete title.t;
}

void TitleScene::draw()
{
    int posx = Settings::getInstance()->getW() / 100, posy = Settings::getInstance()->getH() / 100;
    ///POSITION

    Graphics::getInstance()->drawSprite(window, title,
                         posx, posy);
}

void TitleScene::process()
{
}


