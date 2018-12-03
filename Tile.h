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
enum {LU = 0,RU = 1,LD = 2,RD = 3};

class Tile
{
    public:
        Tile();
        ~Tile();

        Point getTexCoords() const;
        Point getSecondaryTexCoords() const;
        void setPos(int i, int j);
        void setVal(int val);
        void setTex(int val);
        void setHalfTex(int val);
        void setHalfHorizontal(bool i);
        bool isHalfHorizontal() const;
        int getVal() const;
        int getTex() const;
        int getHalfTex() const;
        void setCorner(bool val, int i);
        void setMap(Map* i);
        bool isSolid() const;
        void setSolid(bool i);
        bool getCorner(int i) const;
    private:
        void init();

        Map* map;
        int x;
        int y;
        int val;
        int tex;
        int halftex;
        bool halfhorizontal;
        bool corner[4];
        bool solid;
};

