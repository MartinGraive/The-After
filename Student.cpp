/*THE AFTER
Commenc� le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include <cmath>
#include "Student.h"
#include "GameCore.h"
#include "Map.h"
#include "MainPlayer.h"
#include "Room.h"

Student::Student(Texture t, RenderingArray* a) : Character(a), follow(NULL), followRank(0)
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
        //goTo(23*TILE_SIZE, 5*TILE_SIZE);
        //goToRandomRoom();
        if (follow != NULL) {
            moveToFollowingTarget();
        }
        else {
            randomWalk();
        }
    }
    else {
        moveToDestination();
    }

    if (follow != NULL)
        mayStopFollowing();

    for (int i = 0 ; i < GameCore::getInstance()->getMap()->getNbExits() ; i++) {
        Rect safeZone = GameCore::getInstance()->getMap()->getSafeZone(i);
        if (follow != NULL && !goingToDestination && getXbase() <= (safeZone.x + safeZone.w) * TILE_SIZE && getXbase() + getBaseRect().w >= safeZone.x * TILE_SIZE &&
            getYbase() <= (safeZone.y + safeZone.h) * TILE_SIZE && getYbase() + getBaseRect().h >= safeZone.y * TILE_SIZE) {

            Point exit = GameCore::getInstance()->getMap()->getExit(i);
            unFollow();
            goTo(exit.x * TILE_SIZE, exit.y * TILE_SIZE);
        }
    }

    addBubbleTime();
}

void Student::randomWalk()
{
    moveForward();

    int random = (rand() % 100);
    if (random <= 3) { setDirection(random); }
}

void Student::moveToFollowingTarget()
{
    double xbefore = getXbase(), ybefore = getYbase();
    double xd = 0, yd = 0;
    if (getXbase() + getBaseRect().w * 3 / 4 < follow->getXbase() + follow->getBaseRect().w / 4) {
        xd += speed;
    }
    else if (getXbase() + follow->getBaseRect().w / 4 > follow->getXbase() + follow->getBaseRect().w * 3 / 4) {
        xd -= speed;
    }
    if (getYbase() + getBaseRect().h * 3 / 4 < follow->getYbase() + follow->getBaseRect().h / 4) {
        yd += speed;
    }
    else if (getYbase() + getBaseRect().h / 4 > follow->getYbase() + follow->getBaseRect().h * 3 / 4) {
        yd -= speed;
    }
    move(xd, yd);
    if (xbefore == getXbase() && ybefore == getYbase()) {
        setTypeAnim(STILL);
    }
}

void Student::goToRandomRoom()
{
    int random = (rand() % GameCore::getInstance()->getMap()->getNbRooms());
    goTo(GameCore::getInstance()->getMap()->getRoom(random).getXCenter() * TILE_SIZE,
         GameCore::getInstance()->getMap()->getRoom(random).getYCenter() * TILE_SIZE);
}

void Student::followCharacter(Character* i)
    { follow = i; }

void Student::activate()
{
    if (follow == NULL) {
        MainPlayer* m = GameCore::getInstance()->getMPlayer();
        if (!m->isFollowStackEmpty()) {
            followCharacter(m->lastFollowed());
        }
        else {
            followCharacter(m);
        }
        m->addToFollowStack(this);
        followRank = m->followStackSize();
        goingToDestination = false;

        m->catchStudent();
    }
}

void Student::mayStopFollowing()
{
    MainPlayer* m = GameCore::getInstance()->getMPlayer();
    if (followRank == m->followStackSize()) {
        int dist = std::abs(getXbase() - m->getXbase()) + std::abs(getYbase() - m->getYbase());
        int chance = 10000 - followRank * 1000 - 20 * dist;
        if (chance < 500) { chance = 500; }

        if (rand() % chance == chance - 1 || dist >= 300) {
            unFollow();
            goToRandomRoom();
        }
    }
}

void Student::unFollow()
{
    follow = NULL;
    followRank = 0;
    GameCore::getInstance()->getMPlayer()->unstackFollow();
}

void Student::arrivedAtDestination()
{
    //on verifie que sa destination �tait une sortie
    for (int i = 0 ; i < GameCore::getInstance()->getMap()->getNbExits() ; i++) {
        Point exit = GameCore::getInstance()->getMap()->getExit(i);
        if (finaltarget.x == exit.x * TILE_SIZE + TILE_SIZE / 2 && finaltarget.y == exit.y * TILE_SIZE + TILE_SIZE / 2) {
            //si oui, il sort
            GameCore::getInstance()->removeCharacter(this);
        }
    }
}
