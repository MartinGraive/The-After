/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include "Student.h"
#include "GameCore.h"
#include "Map.h"
#include "MainPlayer.h"

Student::Student(Texture t, RenderingArray* a) : Character(a)
{
    tex = t;
    speed = 0.5;
    solid = false;
}

Student::~Student()
{
}

void Student::process()
{
    if (!goingToDestination) {
        //randomWalk();
        //goTo(23*TILE_SIZE, 5*TILE_SIZE);
        followCharacter(GameCore::getInstance()->getMPlayer());
    }
    else {
        moveToDestination();
    }
}

void Student::randomWalk()
{
    moveForward();

    int random = (rand() % 100);
    if (random < 3) { setDirection(random); }
}

void Student::followCharacter(Character* i)
{
    double xbefore = getXbase(), ybefore = getYbase();
    double xd = 0, yd = 0;
    if (getXbase() + getBaseRect().w * 3 / 4 < i->getXbase() + i->getBaseRect().w / 4) {
        xd += speed;
    }
    else if (getXbase() + i->getBaseRect().w / 4 > i->getXbase() + i->getBaseRect().w * 3 / 4) {
        xd -= speed;
    }
    if (getYbase() + getBaseRect().h * 3 / 4 < i->getYbase() + i->getBaseRect().h / 4) {
        yd += speed;
    }
    else if (getYbase() + getBaseRect().h / 4 > i->getYbase() + i->getBaseRect().h * 3 / 4) {
        yd -= speed;
    }
    move(xd, yd);
    if (xbefore == getXbase() && ybefore == getYbase()) {
        setTypeAnim(STILL);
    }
}
