/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include "MainPlayer.h"

MainPlayer::MainPlayer(RenderingArray* a) : Character(a)
{
}

MainPlayer::~MainPlayer()
{
}

void MainPlayer::move(double xt, double yt)
{
    if (typeanim == STILL) {setTypeAnim(MOVE);}
    setX(getX() + xt);
    setY(getY() + yt);

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
