/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#pragma once

#include "RoomMask.h"
#include "Settings.h"
#include "Map.h"

class Room
{
    public:
        Room(int x, int y, int w, int h, Map* p);
        void drawMask(sf::RenderWindow* window);
        void process();
    private:
        Rect roomRect;
        RoomMask mask;
        sf::RectangleShape interiorMask;
        Map* parent;
        bool entered;
        float fadeEntering;
};


