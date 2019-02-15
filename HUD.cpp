/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include <sstream>
#include "HUD.h"
#include "Graphics/Graphics.h"
#include "Graphics/FontHandler.h"
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
    drawStars(window);
    drawChrono(window);
}

void HUD::drawStars(sf::RenderWindow* window)
{
    int posx = 10 + GameCore::getInstance()->getMPlayer()->getX() - Settings::getInstance()->getW() / 4;
    int posy = 25 + GameCore::getInstance()->getMPlayer()->getY() - Settings::getInstance()->getH() / 4;

    int level = (GameCore::getInstance()->getNbCharacters() * 5) / MAX_STUDENTS;

    int clipx = 0, clipy = 21 * level, clipw = 100, cliph = 21;
    Graphics::getInstance()->drawSprite(window, TextureHandler::getInstance()->getStars(),
                         posx, posy, clipx, clipy, clipw, cliph);
}

void HUD::drawChrono(sf::RenderWindow* window)
{
    sf::Text text;
    text.setFont(*FontHandler::getInstance()->getFont());
    text.setString(formatTime(GameCore::getInstance()->getElapsedTime()));
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::White);
    text.setPosition(GameCore::getInstance()->getMPlayer()->getXbase() + Settings::getInstance()->getW() / 4 - 80,
                     GameCore::getInstance()->getMPlayer()->getYbase() - Settings::getInstance()->getH() / 4 + 10);
    window->draw(text);
}

std::string HUD::formatTime(int frames)
{
    return formatNumber(frames / 60000) + ":" + formatNumber((frames / 1000) % 60) + ":" + formatNumber((frames / 10) % 100);
}

std::string HUD::formatNumber(int num)
{
    std::ostringstream im;
    im << num;
    if (num < 10) { return "0"+im.str(); }
    else { return im.str(); }
}

