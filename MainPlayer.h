/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse

Projet de TDLog*/

#pragma once

#include "Character.h"

class MainPlayer : public Character
{
    public:
        MainPlayer(RenderingArray* a = NULL);
        ~MainPlayer();
        void move(double xt, double yt);
    private:
};
