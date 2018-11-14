/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse

Projet de TDLog*/

#pragma once

#include <SFML/Graphics.hpp>

class Map;

enum {HERBE = 270,VIDE = 258,MONTAGNE = 227,EAU = 36};
enum {LU,LD,RU,RD};

class Tile
{
    public:
        Tile();
        ~Tile();

        void draw(sf::RenderWindow* window);
        void setPos(int i, int j);
        void setCouches(int co1, int co2);
        int getC1() const;
        int getC2() const;
        void setCorner(bool val, int i);
        void setMap(Map* i);
        bool isSolid() const;
    private:
        void drawCouche1(sf::RenderWindow* window);
        void drawCouche2(sf::RenderWindow* window);
        void init();

        Map* map;
        int x;
        int y;
        int c1;
        int c2;
        bool corner[4];
        bool solid;

        sf::Sprite sprite1;
        sf::Sprite sprite2;
};

