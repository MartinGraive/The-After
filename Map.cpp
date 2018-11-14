/*THE AFTER
Commencé le 22/10/2018

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
    /*for (int i = 0 ; i < Settings::getInstance()->getW()/TILE_SIZE + 1 ; i++) {
        for (int j = 0 ; j < Settings::getInstance()->getH()/TILE_SIZE + 2 ; j++) {
            int newi = i + Camera::getInstance()->getPhg(0)/TILE_SIZE;
            int newj = j + Camera::getInstance()->getPhg(1)/TILE_SIZE;
            if (newi < w && newj < h) {tiles[newi][newj].draw(window);}
        }
    }*/
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
            tiles[i][j].setCouches(HERBE, VIDE);
        }
    }
    randomMap();

    autotile(); ///SET AUTOTILESGame::getMPlayer()->getXbase() - Settings::getInstance()->W()/2;
    int *tiles_val = new int[w*h];
    for (int i = 0 ; i < w ; i++) {
        for (int j = 0 ; j < h ; j++) {
            tiles_val[i + j * w] = tiles[i][j].getC1();
        }
    }
    tilemap.prepare("data/graphics/tiles/Basis.png", tiles_val, w, h);
}

void Map::randomMap()
{
    ///DRAWING PATH
    float** heightmap = heightMap(w, h, 3, 2);

    for (int i = 0 ; i < w ; i++) {
        for (int j = 0 ; j < h ; j++) {
            int val = heightmap[i][j] * 12.f;
            if (val >= 0 && val <= 1) { tiles[i][j].setCouches(210, VIDE); }
            else if (val == 2) { tiles[i][j].setCouches(120, VIDE); }
            else if (val == 3) { tiles[i][j].setCouches(70, VIDE); }
            else if (val >= 4 && val <= 7) { tiles[i][j].setCouches(HERBE, VIDE); }
            else if (val == 8) { tiles[i][j].setCouches(67, VIDE); }
            else { tiles[i][j].setCouches(424, VIDE); }
        }
    }

    for (int i = 0 ; i < w ; i++) { delete[] heightmap[i]; }
    delete[] heightmap;
}

void Map::autotile()
{
    for (int i = 0 ; i < w ; i++) {
        for (int j = 0 ; j < h ; j++) {
            int t = tiles[i][j].getC1();
            if (t == EAU) {
                ///corners
                if (i > 0 && j > 0 && tiles[i-1][j-1].getC1() != t && tiles[i-1][j].getC1() == t && tiles[i][j-1].getC1() == t) {
                    tiles[i][j].setCorner(true, LU);
                }
                if (i > 0 && j < h-1 && tiles[i-1][j+1].getC1() != t && tiles[i-1][j].getC1() == t && tiles[i][j+1].getC1() == t) {
                    tiles[i][j].setCorner(true, LD);
                }
                if (i < w-1 && j > 0 && tiles[i+1][j-1].getC1() != t && tiles[i+1][j].getC1() == t && tiles[i][j-1].getC1() == t) {
                    tiles[i][j].setCorner(true, RU);
                }
                if (i < w-1 && j < h-1 && tiles[i+1][j+1].getC1() != t && tiles[i+1][j].getC1() == t && tiles[i][j+1].getC1() == t) {
                    tiles[i][j].setCorner(true, RD);
                }

                ///REST
                if (i > 0 && j > 0 && i < w - 1 && tiles[i-1][j].getC1() != t && tiles[i][j-1].getC1() != t && tiles[i+1][j].getC1() != t) {
                    tiles[i][j].setCouches(t, 27);
                }
                else if (i > 0 && j > 0 && j < h - 1 && tiles[i-1][j].getC1() != t && tiles[i][j-1].getC1() != t && tiles[i][j+1].getC1() != t) {
                    tiles[i][j].setCouches(t, 28);
                }
                else if (i > 0 && j < h-1 && i < w - 1 && tiles[i-1][j].getC1() != t && tiles[i][j+1].getC1() != t && tiles[i+1][j].getC1() != t) {
                    tiles[i][j].setCouches(t, 29);
                }
                else if (i < w-1 && j > 0 && j < h - 1 && tiles[i+1][j].getC1() != t && tiles[i][j-1].getC1() != t && tiles[i][j+1].getC1() != t) {
                    tiles[i][j].setCouches(t, 30);
                }
                else if (i > 0 && j > 0 && tiles[i-1][j].getC1() != t && tiles[i][j-1].getC1() != t) {
                    tiles[i][j].setCouches(t, 0);
                }
                else if (i < w - 1 && j > 0 && tiles[i+1][j].getC1() != t && tiles[i][j-1].getC1() != t) {
                    tiles[i][j].setCouches(t, 2);
                }
                else if (i < w - 1 && j < h -1 && tiles[i+1][j].getC1() != t && tiles[i][j+1].getC1() != t) {
                    tiles[i][j].setCouches(t, 20);
                }
                else if (i > 0 && j < h -1 && tiles[i-1][j].getC1() != t && tiles[i][j+1].getC1() != t) {
                    tiles[i][j].setCouches(t, 18);
                }
                else if (j > 0 && j < h - 1 && tiles[i][j-1].getC1() != t && tiles[i][j+1].getC1() != t) {
                    tiles[i][j].setCouches(t, 22);
                }
                else if (i > 0 && i < w - 1 && tiles[i-1][j].getC1() != t && tiles[i+1][j].getC1() != t) {
                    tiles[i][j].setCouches(t, 29);
                }
                else if (j > 0 && tiles[i][j-1].getC1() != t) {
                    tiles[i][j].setCouches(t, 1);
                }
                else if (i > 0 && tiles[i-1][j].getC1() != t) {
                    tiles[i][j].setCouches(t, 9);
                }
                else if (i < w-1 && tiles[i+1][j].getC1() != t) {
                    tiles[i][j].setCouches(t, 11);
                }
                else if (j < h-1 && tiles[i][j+1].getC1() != t) {
                    tiles[i][j].setCouches(t, 19);
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

