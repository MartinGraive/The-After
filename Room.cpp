/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include "Room.h"
#include "Graphics/TextureHandler.h"
#include "GameCore.h"
#include "MainPlayer.h"

Room::Room(int x, int y, int w, int h, Map* p) : roomRect(x, y, w, h), parent(p), entered(false), fadeEntering(0)
{
    mask.prepare(TextureHandler::getInstance()->getTileset(), p->getW() * TILE_SIZE, p->getH() * TILE_SIZE, roomRect);
    interiorMask.setSize(sf::Vector2f(roomRect.w * TILE_SIZE, roomRect.h * TILE_SIZE - TILE_SIZE / 2));
}

void Room::drawMask(sf::RenderWindow* window)
{
    mask.setPosition(0, 0);
    mask.setFillColor(sf::Color(0,0,0,fadeEntering * 255));
    interiorMask.setPosition(roomRect.x * TILE_SIZE, roomRect.y * TILE_SIZE);
    interiorMask.setFillColor(sf::Color(0,0,0,(1 - fadeEntering) * 255));
    window->draw(mask);
    window->draw(interiorMask);
}

void Room::process()
{
    //if the player is inside the room
    if (GameCore::getInstance()->getMPlayer()->getXbase() + GameCore::getInstance()->getMPlayer()->getBaseRect().w >= roomRect.x * TILE_SIZE &&
        GameCore::getInstance()->getMPlayer()->getXbase() <= (roomRect.x + roomRect.w) * TILE_SIZE &&
        GameCore::getInstance()->getMPlayer()->getYbase() + GameCore::getInstance()->getMPlayer()->getBaseRect().h >= roomRect.y * TILE_SIZE &&
        GameCore::getInstance()->getMPlayer()->getYbase() <= (roomRect.y + roomRect.h) * TILE_SIZE) {

        entered = true;
    }
    else {
        entered = false;
    }

    if (entered) {
        fadeEntering += 0.02;
        if (fadeEntering > 1) {
            fadeEntering = 1;
        }
    }
    else {
        fadeEntering -= 0.02;
        if (fadeEntering < 0) {
            fadeEntering = 0;
        }
    }
}
