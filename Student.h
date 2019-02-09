/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "RenderingArray.h"
#include "Settings.h"
#include "Character.h"

class Student : public Character
{
    public:
        Student(Texture t, RenderingArray* a = NULL);
        ~Student();

        void process();
        void followCharacter(Character* i);
        void goToRandomRoom();

        void activate();

        void arrivedAtDestination();
    private:
        void randomWalk();
        void moveToFollowingTarget();
        void mayStopFollowing();
        void unFollow();

        Character* follow;
        int followRank;
};
