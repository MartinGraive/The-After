/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include "Camera.h"
#include "GameCore.h"
#include "Character.h"

Camera::Camera(sf::RenderWindow* win) : window(win)
{
    view.reset(sf::FloatRect(0, 0, Settings::getInstance()->getW() / 2, Settings::getInstance()->getH() / 2));
    window->setView(view);
}

void Camera::process()
{
}

int Camera::getPhg(int i) const
    { return phg[i]; }

void Camera::scrollScreen(int x, int y)
{
    sf::Vector2f center = view.getCenter();
    if (center.x < 0) { center.x = 0; }
    else if (center.x > GameCore::getInstance()->getMap()->getW()*TILE_SIZE-Settings::getInstance()->getW()) {
        center.x = GameCore::getInstance()->getMap()->getW()*TILE_SIZE-Settings::getInstance()->getW();
    }
    if (center.y < 0) { center.y = 0; }
    else if (center.y > GameCore::getInstance()->getMap()->getH()*TILE_SIZE-Settings::getInstance()->getH()) {
        center.y = GameCore::getInstance()->getMap()->getH()*TILE_SIZE-Settings::getInstance()->getH();
    }
    view.setCenter(center);
}

void Camera::autoScroll()
{
    sf::Vector2f center;
    center.x = GameCore::getInstance()->getMPlayer()->getXbase();
    center.y = GameCore::getInstance()->getMPlayer()->getYbase();
    view.setCenter(center);
    window->setView(view);

    if (phg[0] < 0) { phg[0] = 0; }
    else if (phg[0] > GameCore::getInstance()->getMap()->getW()*TILE_SIZE-Settings::getInstance()->getW()) {
        phg[0] = GameCore::getInstance()->getMap()->getW()*TILE_SIZE-Settings::getInstance()->getW();
    }
    if (phg[1] < 0) { phg[1] = 0; }
    else if (phg[1] > GameCore::getInstance()->getMap()->getH()*TILE_SIZE-Settings::getInstance()->getH()) {
        phg[1] = GameCore::getInstance()->getMap()->getH()*TILE_SIZE-Settings::getInstance()->getH();
    }
}

