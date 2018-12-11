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
#include "Tile.h"
#include "TileMap.h"

class Tile;

class Map
{
    public:
        Map();
        ~Map();

        void drawFloor(sf::RenderWindow* window);
        void drawCeil(sf::RenderWindow* window);
        void create();
        void loadMap(int i);
        int getAnim() const;
        Tile getTile(int i, int j) const;
        Tile getTileCeil(int i, int j) const;
        int getW() const;
        int getH() const;
    private:
        void couloir(int type, int i, int j);
        
        void autotile(std::vector<std::vector<Tile> >& vt);
        void randomMap();
        void loadTileRules();

        int w;
        int h;
        std::vector<std::vector<Tile> > tiles;
        std::vector<std::vector<Tile> > tiles_ceil;
        TileMap tilemap;
        TileMap tilemap_ceil;
        sf::Clock clock;
        int anim;
};

