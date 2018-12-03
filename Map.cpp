/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include <fstream>
#include <sstream>
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

void Map::drawFloor(sf::RenderWindow* window)
{
    window->draw(tilemap);

    if (clock.getElapsedTime().asMilliseconds() >= 180) {
        anim ++;
        if (anim >= 4) { anim = 0; }
        clock.restart();
    }
}

void Map::drawCeil(sf::RenderWindow* window)
{
    window->draw(tilemap_ceil);
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

    tiles[10][10].setVal(70);
    tiles[11][10].setVal(70);
    tiles[11][11].setVal(70);
    tiles[12][11].setVal(70);

    autotile(tiles); ///SET AUTOTILESGame::getMPlayer()->getXbase() - Settings::getInstance()->W()/2;
    tilemap.prepare(Settings::getInstance()->getPath()+"data/graphics/tiles/Basis.png", tiles, w, h);
}

void Map::loadTileRules()
{
    std::ifstream fichier((Settings::getInstance()->getPath()+"data/graphics/tiles/chipset.mmo").c_str(),std::ios::in|std::ios::binary);
    if (fichier) {
        int v=0;
        fichier.read((char*)&v,sizeof(int));
        int* spe=new int[TILESET_WIDTH * 16];
        for (int i=0 ; i<TILESET_WIDTH ; i++)
        {
            for (int j = 0 ; j < 16 ; j++) {
                int val = 0;
                fichier.read((char*)&val,sizeof(int));
                spe[j * TILESET_WIDTH + i]=val;
            }
        }
        fichier.close();

        for (int i=0 ; i<w ; i++)
        {
            for (int j=0 ; j<h ; j++)
            {
                int t = tiles[i][j].getVal();
                if (spe[t] == 1) {
                    tiles[i][j].setSolid(true);
                }
                else if (spe[t] == 2 && t % TILESET_WIDTH <= 12 && (t % TILESET_WIDTH) / 3 == 1 && (t / TILESET_WIDTH) / 4 == 2) { // star tile + autotile
                    if (!(j > 0 && tiles[i][j-1].getVal() != t)) {
                        tiles[i][j].setSolid(true);
                    }
                }
                if (spe[t] == 2) {
                    tiles_ceil[i][j].setVal(t);
                }
            }
        }
        delete[] spe;
    }
}

void Map::loadMap(int i)
{
    //std::cout<<"COUCOU!\n";
    std::ostringstream im;
    im << i;
    std::ifstream fichier((Settings::getInstance()->getPath()+"data/maps/map"+im.str()+".mmo").c_str(),std::ios::in|std::ios::binary);
    int chipset = 0;
    fichier.read((char*)&chipset,sizeof(int));
    fichier.read((char*)&w,sizeof(int));
    fichier.read((char*)&h,sizeof(int));
    tiles.resize(w);
    tiles_ceil.resize(w);
    for (int i = 0 ; i < w ; i++) {
        tiles[i].resize(h);
        tiles_ceil[i].resize(h);
    }

    for (int i=0 ; i<w ; i++)
    {
        for (int j=0 ; j<h ; j++)
        {
            int val;
            fichier.read((char*)&val,sizeof(int));
            tiles[i][j].setMap(this);
            tiles[i][j].setPos(i,j);
            tiles[i][j].setVal(val);

            tiles_ceil[i][j].setMap(this);
            tiles_ceil[i][j].setPos(i,j);
            tiles_ceil[i][j].setVal(VIDE);
        }
    }
    fichier.close();
    loadTileRules();
    autotile(tiles); ///SET AUTOTILESGame::getMPlayer()->getXbase() - Settings::getInstance()->W()/2;
    autotile(tiles_ceil);
    tilemap.prepare(Settings::getInstance()->getPath()+"data/graphics/tiles/chipset.png", tiles, w, h);
    tilemap_ceil.prepare(Settings::getInstance()->getPath()+"data/graphics/tiles/chipset.png", tiles_ceil, w, h);
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

void Map::autotile(std::vector<std::vector<Tile> >& vt)
{
    for (int i = 0 ; i < w ; i++) {
        for (int j = 0 ; j < h ; j++) {
            int t = vt[i][j].getVal();
            if (t % TILESET_WIDTH <= 12 && (t % TILESET_WIDTH) / 3 == 1 && (t / TILESET_WIDTH) / 4 == 2) {
                // opposite corners
                if (i > 0 && j > 0 && vt[i-1][j-1].getVal() != t && vt[i-1][j].getVal() == t && vt[i][j-1].getVal() == t) {
                    vt[i][j].setCorner(true, LU);
                }
                if (i > 0 && j < h-1 && vt[i-1][j+1].getVal() != t && vt[i-1][j].getVal() == t && vt[i][j+1].getVal() == t) {
                    vt[i][j].setCorner(true, LD);
                }
                if (i < w-1 && j > 0 && vt[i+1][j-1].getVal() != t && vt[i+1][j].getVal() == t && vt[i][j-1].getVal() == t) {
                    vt[i][j].setCorner(true, RU);
                }
                if (i < w-1 && j < h-1 && vt[i+1][j+1].getVal() != t && vt[i+1][j].getVal() == t && vt[i][j+1].getVal() == t) {
                    vt[i][j].setCorner(true, RD);
                }

                // other tile rules
                if (i > 0 && j > 0 && i < w - 1 && vt[i-1][j].getVal() != t && vt[i][j-1].getVal() != t && vt[i+1][j].getVal() != t) {
                    //  _
                    // | |
                    vt[i][j].setTex(t - 1 * TILESET_WIDTH - 1);
                    vt[i][j].setHalfTex(t - 1 * TILESET_WIDTH + 1);
                    vt[i][j].setHalfHorizontal(true);
                }
                else if (i > 0 && j > 0 && j < h - 1 && vt[i-1][j].getVal() != t && vt[i][j-1].getVal() != t && vt[i][j+1].getVal() != t) {
                    //  _
                    // |_
                    vt[i][j].setTex(t - 1 * TILESET_WIDTH - 1);
                    vt[i][j].setHalfTex(t + 1 * TILESET_WIDTH - 1);
                    vt[i][j].setHalfHorizontal(false);
                }
                else if (i > 0 && j < h-1 && i < w - 1 && vt[i-1][j].getVal() != t && vt[i][j+1].getVal() != t && vt[i+1][j].getVal() != t) {
                    // |_|
                    vt[i][j].setTex(t + 1 * TILESET_WIDTH - 1);
                    vt[i][j].setHalfTex(t + 1 * TILESET_WIDTH + 1);
                    vt[i][j].setHalfHorizontal(true);
                }
                else if (i < w-1 && j > 0 && j < h - 1 && vt[i+1][j].getVal() != t && vt[i][j-1].getVal() != t && vt[i][j+1].getVal() != t) {
                    // _
                    // _|
                    vt[i][j].setTex(t - 1 * TILESET_WIDTH + 1);
                    vt[i][j].setHalfTex(t + 1 * TILESET_WIDTH + 1);
                    vt[i][j].setHalfHorizontal(false);
                }
                else if (i > 0 && j > 0 && vt[i-1][j].getVal() != t && vt[i][j-1].getVal() != t) {
                    //  _
                    // |
                    vt[i][j].setTex(t - 1 * TILESET_WIDTH - 1);
                }
                else if (i < w - 1 && j > 0 && vt[i+1][j].getVal() != t && vt[i][j-1].getVal() != t) {
                    //  _
                    //   |
                    vt[i][j].setTex(t - 1 * TILESET_WIDTH + 1);
                }
                else if (i < w - 1 && j < h -1 && vt[i+1][j].getVal() != t && vt[i][j+1].getVal() != t) {
                    // _|
                    vt[i][j].setTex(t + 1 * TILESET_WIDTH + 1);
                }
                else if (i > 0 && j < h -1 && vt[i-1][j].getVal() != t && vt[i][j+1].getVal() != t) {
                    // |_
                    vt[i][j].setTex(t + 1 * TILESET_WIDTH - 1);
                }
                else if (j > 0 && j < h - 1 && vt[i][j-1].getVal() != t && vt[i][j+1].getVal() != t) {
                    //  _
                    //  _
                    vt[i][j].setTex(t - 1 * TILESET_WIDTH);
                    vt[i][j].setHalfTex(t + 1 * TILESET_WIDTH);
                    vt[i][j].setHalfHorizontal(false);
                }
                else if (i > 0 && i < w - 1 && vt[i-1][j].getVal() != t && vt[i+1][j].getVal() != t) {
                    // | |
                    vt[i][j].setTex(t - 1);
                    vt[i][j].setHalfTex(t + 1);
                    vt[i][j].setHalfHorizontal(true);
                }
                else if (j > 0 && vt[i][j-1].getVal() != t) {
                    //  _
                    //
                    vt[i][j].setTex(t - 1 * TILESET_WIDTH);
                }
                else if (i > 0 && vt[i-1][j].getVal() != t) {
                    // |
                    vt[i][j].setTex(t - 1);
                }
                else if (i < w-1 && vt[i+1][j].getVal() != t) {
                    //   |
                    vt[i][j].setTex(t + 1);
                }
                else if (j < h-1 && vt[i][j+1].getVal() != t) {
                    //
                    //  _
                    vt[i][j].setTex(t + 1 * TILESET_WIDTH);
                }
            }
        }
    }
}

int Map::getAnim() const
    { return anim; }

Tile Map::getTile(int i, int j) const
    { return tiles[i][j]; }

Tile Map::getTileCeil(int i, int j) const
    { return tiles_ceil[i][j]; }

int Map::getW() const
    { return w; }

int Map::getH() const
    { return h; }

