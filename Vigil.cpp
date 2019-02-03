/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include "Vigil.h"
#include "GameCore.h"
#include "Map.h"
#include "MainPlayer.h"

Vigil::Vigil(Texture t, RenderingArray* a) : Character(a)
{
    tex = t;
    speed = 0.5;
}

Vigil::~Vigil()
{
}

void Vigil::process()
{
    goStraightTurnRight();

    if (!isSpeaking() && seesPlayer()) {
        say(L"Eh toi je te connais !");
    }
}

/// Checks if player is in the vigil's visibility zone
/// then traces lines between them to see if there's an obstacle in the way
bool Vigil::seesPlayer()
{
    Rect visibleZone;
    if (direction == HAUT) {
        visibleZone.w = TILE_SIZE * 4;
        visibleZone.h = TILE_SIZE * 10;
        visibleZone.x = getXbase() + getBaseRect().w / 2 - visibleZone.w / 2;
        visibleZone.y = getYbase() - visibleZone.h;
    }
    else if (direction == BAS) {
        visibleZone.w = TILE_SIZE * 4;
        visibleZone.h = TILE_SIZE * 10;
        visibleZone.x = getXbase() + getBaseRect().w / 2 - visibleZone.w / 2;
        visibleZone.y = getYbase() + getBaseRect().h;
    }
    else if (direction == GAUCHE) {
        visibleZone.w = TILE_SIZE * 10;
        visibleZone.h = TILE_SIZE * 4;
        visibleZone.y = getYbase() + getBaseRect().h / 2 - visibleZone.h / 2;
        visibleZone.x = getXbase() - visibleZone.w;
    }
    else if (direction == DROITE) {
        visibleZone.w = TILE_SIZE * 10;
        visibleZone.h = TILE_SIZE * 4;
        visibleZone.y = getYbase() + getBaseRect().h / 2 - visibleZone.h / 2;
        visibleZone.x = getXbase() + getBaseRect().w;
    }

    MainPlayer* m = GameCore::getInstance()->getMPlayer();
    if (m->isInRect(visibleZone)) {
        int xmc = m->getXbase() + m->getBaseRect().w / 2;
        int ymc = m->getYbase() + m->getBaseRect().h / 2;
        int xvc = getXbase() + getBaseRect().w / 2;
        int yvc = getYbase() + getBaseRect().h / 2;
        //pente infinie
        if (xvc / TILE_SIZE == xmc / TILE_SIZE) {
            int s = std::min(yvc / TILE_SIZE, ymc / TILE_SIZE);
            int e = s + abs(yvc - ymc) / TILE_SIZE;
            for (int i = s ; i <= e ; i++) {
                if (GameCore::getInstance()->getMap()->getTile(xvc / TILE_SIZE, i).isSolid()) {
                    return false;
                }
            }
            return true;
        }
        else { //pente finie
            double coeff = (ymc - yvc) / (xmc - yvc);
            //si la pente est < 1
            if (coeff <= 1) {
                double y_current = ymc;
                int s = std::min(xvc / TILE_SIZE, xmc / TILE_SIZE);
                int e = s + abs(xvc - xmc) / TILE_SIZE;
                for (int i = s ; i <= e ; i++) {
                    if (GameCore::getInstance()->getMap()->getTile(i, y_current / TILE_SIZE).isSolid()) {
                        return false;
                    }
                    y_current += coeff;
                }
                return true;
            }
            else {
                double x_current = xmc;
                int s = std::min(yvc / TILE_SIZE, ymc / TILE_SIZE);
                int e = s + abs(yvc - ymc) / TILE_SIZE;
                for (int i = s ; i <= e ; i++) {
                    if (GameCore::getInstance()->getMap()->getTile(x_current / TILE_SIZE, i).isSolid()) {
                        return false;
                    }
                    x_current += 1/coeff;
                }
                return true;
            }
        }
    }
    return false;
}

void Vigil::goStraightTurnRight()
{
    moveForward();

    //if obstacle : turn right
    double x_in_front = getXbase() + getBaseRect().w / 2;
    double y_in_front = getYbase() + getBaseRect().h / 2;
    if (direction == HAUT) { y_in_front -= 1.5 * double(TILE_SIZE); }
    else if (direction == BAS) { y_in_front += 1.5 * double(TILE_SIZE); }
    else if (direction == GAUCHE) { x_in_front -= 1.5 * double(TILE_SIZE); }
    else if (direction == DROITE) { x_in_front += 1.5 * double(TILE_SIZE); }
    x_in_front /= TILE_SIZE;
    y_in_front /= TILE_SIZE;
    if (GameCore::getInstance()->getMap()->getTile(int(x_in_front), int(y_in_front)).isSolid()) {
        turnRight();
    }
}
