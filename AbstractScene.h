/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse

Projet de TDLog*/

#pragma once

class AbstractScene
{
    public:
        virtual ~AbstractScene() {}
        virtual void draw() = 0;
        virtual void process() = 0;
};
