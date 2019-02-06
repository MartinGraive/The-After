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
}

Student::~Student()
{
}

void Student::process()
{
    if (!goingToDestination) {
        //randomWalk();
        goTo(23*TILE_SIZE, 5*TILE_SIZE);
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
