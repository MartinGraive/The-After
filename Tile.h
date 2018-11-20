/*THE AFTER
Commenc� le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#pragma once

#include "Settings.h"

class Map;

enum {HERBE = 270,VIDE = 258,MONTAGNE = 227,EAU = 36};
enum {LU,LD,RU,RD};

class Tile
{
    public:
        Tile();
        ~Tile();

        Point getTexCoords();
        void setPos(int i, int j);
        void setVal(int val);
        int getVal() const;
        void setCorner(bool val, int i);
        void setMap(Map* i);
        bool isSolid() const;
    private:
        void init();

        Map* map;
        int x;
        int y;
        int val;
        bool corner[4];
        bool solid;
};

