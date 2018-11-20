/*THE AFTER
Commenc� le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include "Map.h"
#include "GameCore.h"
#include "Tile.h"
#include "Settings.h"
#include "Camera.h"
#include "MainPlayer.h"
#include "TileMap.h"
#include "Primitives/Perlin.h"

Map::Map() : anim(0)
{
    clock.restart();
}

Map::~Map()
{
}

void Map::draw(sf::RenderWindow* window)
{
    window->draw(tilemap);

    if (clock.getElapsedTime().asMilliseconds() >= 180) {
        anim ++;
        if (anim >= 4) { anim = 0; }
        clock.restart();
    }
}

void Map::create()
{
    w = 128;
    h = 128;
    tiles.resize(w);
    for (int i = 0 ; i < w ; i++) {
        tiles[i].resize(h);
    }

    for (int i = 0 ; i < w ; i++) {
        for (int j = 0 ; j < h ; j++) {
            tiles[i][j].setMap(this);
            tiles[i][j].setPos(i,j);
            tiles[i][j].setVal(HERBE);
        }
    }
    randomMap();

    autotile(); ///SET AUTOTILESGame::getMPlayer()->getXbase() - Settings::getInstance()->W()/2;
    tilemap.prepare("data/graphics/tiles/Basis.png", tiles, w, h);
}

void Map::randomMap()
{
    ///DRAWING PATH
    float** heightmap = heightMap(w, h, 3, 2);

    for (int i = 0 ; i < w ; i++) {
        for (int j = 0 ; j < h ; j++) {
            int val = heightmap[i][j] * 12.f;
            if (val >= 0 && val <= 1) { tiles[i][j].setVal(210); }
            else if (val == 2) { tiles[i][j].setVal(120); }
            else if (val == 3) { tiles[i][j].setVal(70); }
            else if (val >= 4 && val <= 7) { tiles[i][j].setVal(HERBE); }
            else if (val == 8) { tiles[i][j].setVal(67); }
            else { tiles[i][j].setVal(424); }
        }
    }

    for (int i = 0 ; i < w ; i++) { delete[] heightmap[i]; }
    delete[] heightmap;
}

void Map::autotile()
{
    for (int i = 0 ; i < w ; i++) {
        for (int j = 0 ; j < h ; j++) {
            int t = tiles[i][j].getVal();
            if (t == EAU) {
                // opposite corners
                if (i > 0 && j > 0 && tiles[i-1][j-1].getVal() != t && tiles[i-1][j].getVal() == t && tiles[i][j-1].getVal() == t) {
                    tiles[i][j].setCorner(true, LU);
                }
                if (i > 0 && j < h-1 && tiles[i-1][j+1].getVal() != t && tiles[i-1][j].getVal() == t && tiles[i][j+1].getVal() == t) {
                    tiles[i][j].setCorner(true, LD);
                }
                if (i < w-1 && j > 0 && tiles[i+1][j-1].getVal() != t && tiles[i+1][j].getVal() == t && tiles[i][j-1].getVal() == t) {
                    tiles[i][j].setCorner(true, RU);
                }
                if (i < w-1 && j < h-1 && tiles[i+1][j+1].getVal() != t && tiles[i+1][j].getVal() == t && tiles[i][j+1].getVal() == t) {
                    tiles[i][j].setCorner(true, RD);
                }

                // other tile rules
                if (i > 0 && j > 0 && i < w - 1 && tiles[i-1][j].getVal() != t && tiles[i][j-1].getVal() != t && tiles[i+1][j].getVal() != t) {
                    tiles[i][j].setVal(27);
                }
                else if (i > 0 && j > 0 && j < h - 1 && tiles[i-1][j].getVal() != t && tiles[i][j-1].getVal() != t && tiles[i][j+1].getVal() != t) {
                    tiles[i][j].setVal(28);
                }
                else if (i > 0 && j < h-1 && i < w - 1 && tiles[i-1][j].getVal() != t && tiles[i][j+1].getVal() != t && tiles[i+1][j].getVal() != t) {
                    tiles[i][j].setVal(29);
                }
                else if (i < w-1 && j > 0 && j < h - 1 && tiles[i+1][j].getVal() != t && tiles[i][j-1].getVal() != t && tiles[i][j+1].getVal() != t) {
                    tiles[i][j].setVal(30);
                }
                else if (i > 0 && j > 0 && tiles[i-1][j].getVal() != t && tiles[i][j-1].getVal() != t) {
                    tiles[i][j].setVal(0);
                }
                else if (i < w - 1 && j > 0 && tiles[i+1][j].getVal() != t && tiles[i][j-1].getVal() != t) {
                    tiles[i][j].setVal(2);
                }
                else if (i < w - 1 && j < h -1 && tiles[i+1][j].getVal() != t && tiles[i][j+1].getVal() != t) {
                    tiles[i][j].setVal(20);
                }
                else if (i > 0 && j < h -1 && tiles[i-1][j].getVal() != t && tiles[i][j+1].getVal() != t) {
                    tiles[i][j].setVal(18);
                }
                else if (j > 0 && j < h - 1 && tiles[i][j-1].getVal() != t && tiles[i][j+1].getVal() != t) {
                    tiles[i][j].setVal(22);
                }
                else if (i > 0 && i < w - 1 && tiles[i-1][j].getVal() != t && tiles[i+1][j].getVal() != t) {
                    tiles[i][j].setVal(29);
                }
                else if (j > 0 && tiles[i][j-1].getVal() != t) {
                    tiles[i][j].setVal(1);
                }
                else if (i > 0 && tiles[i-1][j].getVal() != t) {
                    tiles[i][j].setVal(9);
                }
                else if (i < w-1 && tiles[i+1][j].getVal() != t) {
                    tiles[i][j].setVal(11);
                }
                else if (j < h-1 && tiles[i][j+1].getVal() != t) {
                    tiles[i][j].setVal(19);
                }
            }
        }
    }
}

int Map::getAnim() const
    { return anim; }

Tile Map::getTile(int i, int j) const
    { return tiles[i][j]; }

int Map::getW() const
    { return w; }

int Map::getH() const
    { return h; }

