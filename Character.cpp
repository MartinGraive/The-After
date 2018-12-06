/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include <cmath>
#include "Character.h"
#include "GameCore.h"
#include "Graphics/Graphics.h"
#include "Graphics/TextureHandler.h"
#include "Primitives/EllipseShape.h"
#include "Settings.h"
#include "Tile.h"
#include "Map.h"
#include "Camera.h"

Character::Character(RenderingArray* a) : direction(1), bubble(NULL)
{
    array = a;
    clock.restart();

    typeanim = STILL;
    anim = 0;
    speed = 1;

    baseRect.x = 4;
    baseRect.y = 16;
    baseRect.w = 16;
    baseRect.h = 16;
    w=24;
    h=32;
    solid = true;
}

Character::~Character()
{
    if (bubble != NULL)
        delete bubble;
}

void Character::draw(sf::RenderWindow* window)
{
    /*if (x < Camera::getInstance()->getPhg(0) - w - TILE_SIZE || x > Camera::getInstance()->getPhg(0) + Settings::getInstance()->getW() + TILE_SIZE
        || y < Camera::getInstance()->getPhg(1) - h - TILE_SIZE || y > Camera::getInstance()->getPhg(1) + Settings::getInstance()->getW() + TILE_SIZE) {
        return;
    }*/

    if (typeanim == STILL || typeanim == MOVE) { drawStillAndMove(window); }

    ///Draw Arrow if selected
}

void Character::drawAbove(sf::RenderWindow* window)
{
    if (bubble != NULL) {
        bubble->draw(window);
    }
}

void Character::drawStillAndMove(sf::RenderWindow* window)
{
    ///DRAW SHADOW
    Graphics::getInstance()->drawEllipse(window, x + baseRect.x + 2, y + baseRect.y + baseRect.h - 5,
                          6, 3, 1, 150);

    ///DRAW CHARACTER
    int posx = 0, posy = 0;
    int clipx = 0;
    ///POSITION
    if (typeanim == MOVE) { posx = x, posy = y; clipx = anim + 1 - 2*(int)(anim/2) - 2*(int)(anim/3);}
    else { posx = x, posy = y; clipx = 1; }
    Graphics::getInstance()->drawSprite(window, tex,
                         posx, posy, clipx*w, direction*h, w, h);

    if (typeanim == MOVE) {
        if (clock.getElapsedTime().asMilliseconds() >= 180) {
            anim ++;
            if (anim >= 4) { anim = 0; }

            clock.restart();
        }
    }
}

void Character::process()
{
}

EntityType Character::getType() const
    { return CHARACTER; }

void Character::move(double xt, double yt)
{
    if (typeanim == STILL) {setTypeAnim(MOVE);}
    if (!collideWithEntities(xt, 0)) {
        setX(getX() + xt);
    }
    if (!collideWithEntities(0, yt)) {
        setY(getY() + yt);
    }

    ///Change direction
    if (direction == HAUT && yt>0 && xt != 0) { direction = BAS;}
    else if (direction == BAS && yt<0 && xt != 0) { direction = HAUT;}
    else if (direction == GAUCHE && yt!=0 && xt > 0) { direction = DROITE;}
    else if (direction == DROITE && yt!=0 && xt < 0) { direction = GAUCHE;}
    else if (yt==0 && xt < 0) { direction = GAUCHE;}
    else if (yt==0 && xt > 0) { direction = DROITE;}
    else if (yt<0 && xt == 0) { direction = HAUT;}
    else if (yt>0 && xt == 0) { direction = BAS;}
    else if (yt>0 && xt == 0) { direction = BAS;}
}

bool Character::collideWithEntities(double xd, double yd)
{
    /// if map blocks
    if (GameCore::getInstance()->getMap()->getTile((getXbase()+xd)/TILE_SIZE,(getYbase()+yd)/TILE_SIZE).isSolid() ||
        GameCore::getInstance()->getMap()->getTile((getXbase()+baseRect.w+xd)/TILE_SIZE,(getYbase()+yd)/TILE_SIZE).isSolid() ||
        GameCore::getInstance()->getMap()->getTile((getXbase()+baseRect.w+xd)/TILE_SIZE,(getYbase()+baseRect.h+yd)/TILE_SIZE).isSolid() ||
        GameCore::getInstance()->getMap()->getTile((getXbase()+xd)/TILE_SIZE,(getYbase()+baseRect.h+yd)/TILE_SIZE).isSolid()) {

        return true;
    }

    ///if Entities block
    for (int i = 0 ; i < GameCore::getInstance()->getEntities()->size() ; i++) {
        Entity* e = GameCore::getInstance()->getEntities()->getEntity(i);
        if (e->getType() == CHARACTER && e->getX() == x && e->getY() == y) { continue; }
        if (e->isSolid() && getXbase() + xd + baseRect.w >= e->getXbase() &&
                            getYbase() + yd + baseRect.h >= e->getYbase() &&
                            getXbase() + xd <= e->getXbase() + e->getBaseRect().w &&
                            getYbase() + yd <= e->getYbase() + e->getBaseRect().h) {
            return true;
        }
    }

    return false;
}

void Character::setTypeAnim(TypeAnim t)
{
    anim = 0;
    typeanim = t;
}

double Character::getSpeed() const
    { return speed; }

void Character::say(std::string i)
{
    bubble = new TextBox(i, x - 10, y - 21);
}
