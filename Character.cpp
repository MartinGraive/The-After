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
#include "Primitives/Astar.h"
#include "Settings.h"
#include "Tile.h"
#include "Map.h"
#include "Camera.h"

Character::Character(RenderingArray* a) : direction(1), speaking(false), bubble(NULL), frameBubble(0), path_step(0), goingToDestination(false)
{
    array = a;
    clock.restart();

    typeanim = STILL;
    anim = 0;
    speed = 1;

    baseRect.x = 5;
    baseRect.y = 17;
    baseRect.w = 14;
    baseRect.h = 15;
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
    Graphics::getInstance()->drawEllipse(window, x + baseRect.x + 1, y + baseRect.y + baseRect.h - 5,
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
    else if (typeanim == STILL) {
        anim = 0;
    }
    setTypeAnim(STILL);
}

void Character::process()
{
    addBubbleTime();
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

void Character::moveForward()
{
    if (direction == HAUT) { move(0, -speed); }
    else if (direction == BAS) { move(0, speed); }
    else if (direction == GAUCHE) { move(-speed, 0); }
    else if (direction == DROITE) { move(speed, 0); }
}

void Character::turnLeft()
{
    direction --;
    if (direction < 0) { direction = 3; }
}

void Character::turnRight()
{
    direction ++;
    if (direction > 3) { direction = 0; }
}

void Character::setDirection(int i)
    { direction = i; }

int Character::getDirection()
    { return direction; }

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
    typeanim = t;
}

double Character::getSpeed() const
    { return speed; }

void Character::say(std::wstring i)
{
    bubble = new TextBox(i, x - 10, y - 21, 100, this);
    speaking = true;
    frameBubble = 0;
}

bool Character::isSpeaking()
    { return speaking; }

void Character::goTo(int xt, int yt)
{
    path = astar(getXbase(), getYbase(), xt, yt);
    std::cout<< "path.size="<<path.size()<<"\n";
    if (path.size() > 0) {
        finaltarget.x = (xt / TILE_SIZE) * TILE_SIZE + TILE_SIZE / 2;
        finaltarget.y = (yt / TILE_SIZE) * TILE_SIZE + TILE_SIZE / 2;
        target.x = path[path.size() - 1].x * TILE_SIZE;
        target.y = path[path.size() - 1].y * TILE_SIZE;
        path_step = 0;
        goingToDestination = true;
    }
}

void Character::moveToDestination()
{
    if (target.x < getXbase()) { move(-speed, 0); }
    else if (target.x > getXbase()) { move(speed, 0); }
    else if (target.y < getYbase()) { move (0, -speed); }
    else if (target.y > getYbase()) { move(0, speed); }

    ///if arrived
    if (getXbase() + baseRect.w  >= finaltarget.x &&
        getYbase() + baseRect.h  >= finaltarget.y &&
        getXbase() <= finaltarget.x &&
        getYbase() <= finaltarget.y)
    {
        typeanim = STILL;
        goingToDestination = false;
        arrivedAtDestination();
    }
    else if (getXbase() + baseRect.w / 2  >= target.x + TILE_SIZE / 2 - 1 && /// if partial path done
        getYbase() + baseRect.h / 2  >= target.y + TILE_SIZE / 2 - 1 &&
        getXbase() + baseRect.w / 2 <= target.x + TILE_SIZE / 2 + 1 &&
        getYbase() + baseRect.h / 2 <= target.y + TILE_SIZE / 2 + 1)
    {
        path_step++;
        target.x = path[path.size() - path_step - 1].x * TILE_SIZE;
        target.y = path[path.size() - path_step - 1].y * TILE_SIZE;
    }
}

void Character::arrivedAtDestination()
{
}

void Character::addBubbleTime()
{
    if (bubble != NULL) {
        frameBubble++;
        if (frameBubble > MAX_FRAME_BUBBLE) {
            stopSpeaking();
        }
    }
}

void Character::stopSpeaking()
{
    speaking = false;
    delete bubble;
    bubble = NULL;
}
