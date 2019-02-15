/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include <fstream>
#include <sstream>
#include "HUD.h"
#include "Graphics/Graphics.h"
#include "GameCore.h"
#include "MainPlayer.h"
#include "Settings.h"

HUD::HUD()
{
}

HUD::~HUD()
{
}

void HUD::draw(sf::RenderWindow* window)
{
    int posx = 10 + GameCore::getInstance()->getMPlayer()->getX() - Settings::getInstance()->getW() / 4;
    int posy = 25 + GameCore::getInstance()->getMPlayer()->getY() - Settings::getInstance()->getH() / 4;

    int level = (GameCore::getInstance()->getNbCharacters() * 5) / MAX_STUDENTS;

    int clipx = 0, clipy = 21 * level, clipw = 100, cliph = 21;
    Graphics::getInstance()->drawSprite(window, TextureHandler::getInstance()->getStars(),
                         posx, posy, clipx, clipy, clipw, cliph);
}

