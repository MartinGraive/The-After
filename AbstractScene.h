/*THE AFTER
Commenc� le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#pragma once

enum{GAME, TITLE, GAMEOVER};

class AbstractScene
{
    public:
        virtual ~AbstractScene() {}
        virtual void draw() = 0;
        virtual void process() = 0;

        virtual int getType() = 0;
};
