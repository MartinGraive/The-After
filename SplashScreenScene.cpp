/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include "SplashScreenScene.h"
#include "GameCore.h"
#include "Graphics/TextureHandler.h"
#include "Graphics/Graphics.h"
#include "GameScene.h"

SplashScreenScene::SplashScreenScene(sf::RenderWindow* win) : window(win), frameElapsed(0)
{
    ki = TextureHandler::getInstance()->loadTexture(Settings::getInstance()->getPath()+"data/graphics/title/ki.png");
}

SplashScreenScene::~SplashScreenScene()
{
    delete ki.t;
}

void SplashScreenScene::draw()
{
    int posx = Settings::getInstance()->getW() / 2 - ki.w / 2, posy = Settings::getInstance()->getH() / 2 - ki.h / 2;
    ///POSITION
    int alpha = 0;
    if (frameElapsed < 50) {
        alpha = frameElapsed * 255 / 50;
    }
    else if (frameElapsed > 200) { alpha = 0; }
    else if (frameElapsed > 150) {
        alpha = 255 - (frameElapsed - 150) * 255 / 50;
    }
    else { alpha = 255; }

    Graphics::getInstance()->drawSprite(window, ki,
                         posx, posy, 1, alpha);
}

void SplashScreenScene::process()
{
    frameElapsed++;
    if (frameElapsed > 250) {
        //go to next scene
        GameScene* scene = new GameScene(window);
        next = scene;
    }
}

