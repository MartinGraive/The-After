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
            tiles[i][j].setVal(FLOOR);
        }
    }
    randomMap();
    
    autotile(tiles); ///SET AUTOTILESGame::getMPlayer()->getXbase() - Settings::getInstance()->W()/2;
    tilemap.prepare(Settings::getInstance()->getPath()+"data/graphics/tiles/chipset.png", tiles, w, h);
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
    if (fichier) {
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
                tiles_ceil[i][j].setVal(EMPTY);
            }
        }
        fichier.close();
        loadTileRules();
        autotile(tiles); ///SET AUTOTILESGame::getMPlayer()->getXbase() - Settings::getInstance()->W()/2;
        autotile(tiles_ceil);
        tilemap.prepare(Settings::getInstance()->getPath()+"data/graphics/tiles/chipset.png", tiles, w, h);
        tilemap_ceil.prepare(Settings::getInstance()->getPath()+"data/graphics/tiles/chipset.png", tiles_ceil, w, h);
    }
}

enum {C_VERT = 1, C_HORI = 2, COUDE_SG = 3, COUDE_SD = 4, COUDE_ID = 5, COUDE_IG = 6, CULDS_D = 7, CULDS_G = 8, CULDS_H = 9, CULDS_B = 10};
void Map::couloir(int type, int i, int j) //(i,j) tile en haut a gauche du rectangle a creer
{
    for (int ii=0;ii<13;ii++)
    {
        for (int jj=0;jj<13;jj++)
        {
            tiles[i+ii][j+jj].setVal(CEILING);
        }
    }
    // oui je sais c'est absurde je pourrais faire toutes les boucles apres le switch...
    switch(type) // format de base 13*13
    {
        case 1: //simple couloir vertical
            for (int ii=0;ii<3;ii++)
            {
                for (int jj=0;jj<13;jj++)
                {
                    tiles[i+5+ii][j+jj].setVal(FLOOR);
                }
            }
            break;
        case 2: // simple couloir horizontal 
            for (int ii=0;ii<13;ii++)
            {
                for (int jj=0;jj<3;jj++)
                {
                    tiles[i+ii][j+5+jj].setVal(FLOOR);
                }
            }
            break;
        case 3: //coin superieur gauche
            for (int ii=5;ii<13;ii++)
            {
                for (int jj=0;jj<3;jj++)
                {
                    tiles[i+ii][j+5+jj].setVal(FLOOR);
                }
            }
            for (int jj=5;jj<13;jj++)
            {
                for (int ii=0;ii<3;ii++)
                {
                    tiles[i+5+ii][j+jj].setVal(FLOOR);
                }
            }
            break;
        case 4: //coin superieur droit
            for (int ii=0;ii<8;ii++)
            {
                for (int jj=0;jj<3;jj++)
                {
                    tiles[i+ii][j+5+jj].setVal(FLOOR);
                }
            }
            for (int jj=5;jj<13;jj++)
            {
                for (int ii=0;ii<3;ii++)
                {
                    tiles[i+5+ii][j+jj].setVal(FLOOR);
                }
            }
            break;
        case 5: //coin inferieur droit
            for (int ii=0;ii<8;ii++)
            {
                for (int jj=0;jj<3;jj++)
                {
                    tiles[i+ii][j+5+jj].setVal(FLOOR);
                }
            }
            for (int jj=0;jj<8;jj++)
            {
                for (int ii=0;ii<3;ii++)
                {
                    tiles[i+5+ii][j+jj].setVal(FLOOR);
                }
            }
            break;
        case 6: //coin inferieur droit
            for (int ii=5;ii<13;ii++)
            {
                for (int jj=0;jj<3;jj++)
                {
                    tiles[i+ii][j+5+jj].setVal(FLOOR);
                }
            }
            for (int jj=0;jj<8;jj++)
            {
                for (int ii=0;ii<3;ii++)
                {
                    tiles[i+5+ii][j+jj].setVal(FLOOR);
                }
            }
            break;
        case 7: //cul de sac horizontal a droite
            for (int ii=0;ii<7;ii++)
            {
                for (int jj=0;jj<3;jj++)
                {
                    tiles[i+ii][j+5+jj].setVal(FLOOR);
                }
            }
            break;
        case 8: //cul de sac horizontal a gauche
            for (int ii=6;ii<13;ii++)
            {
                for (int jj=0;jj<3;jj++)
                {
                    tiles[i+ii][j+5+jj].setVal(FLOOR);
                }
            }
            break;
        case 9: //cul de sac vertical en haut
            for (int ii=0;ii<3;ii++)
            {
                for (int jj=6;jj<13;jj++)
                {
                    tiles[i+5+ii][j+jj].setVal(FLOOR);
                }
            }
            break;
        case 10: //cul de sac vertical en bas
            for (int ii=0;ii<3;ii++)
            {
                for (int jj=0;jj<7;jj++) 
                {
                    tiles[i+5+ii][j+jj].setVal(FLOOR);
                }
            }
            break;
        default:
            std::cerr << "mauvais type de couloir" << std::endl; // erreur
            break;
    }
}

//enum {HAUT = 0,BAS = 2,GAUCHE = 3,DROITE = 1}; // dans Settings.h via Tile.h
enum statut {LIBRE, CLOS, OUVERT};
void Map::randomMap()
{
    if ((w%13!=0) || (h%13!=0)) std::cerr << "la map est de mauvaise dimensions" << std::endl; // erreur dependant de la taille des blocs de couloir
    // initialisation de la map vide :
    for (int i=0 ; i<w ; i++) 
    {
        for (int j=0 ; j<h ; j++)
        {
            tiles[i][j].setVal(EMPTY); // CEILING ou EMPTY ?
        }
    }
    // creation et initialisation du tableau des disponibilites des interfaces entre blocs
    statut** disponibilites = new statut*[w/13+2];
    for (int i=0;i<w/13+2;i++) {
        disponibilites[i] = new statut[h/13+2];
        for (int j=0;j<h/13+2;j++) {
            disponibilites[i][j] = LIBRE;
        }
    }
    for (int i=0;i<w/13+2;i++) {
        disponibilites[i][0]=CLOS;
        disponibilites[i][h/13+1]=CLOS;
    }
    for (int j=0;j<h/13+2;j++) {
        disponibilites[0][j]=CLOS;
        disponibilites[w/13+1][j]=CLOS;
    }
    
    disponibilites[0][(h/13+1)/2]=OUVERT; //entree de la residence
    // appel recursif parcours au depart du bloc 0,(h/13-1)/2
    
    couloir(9,5,5);
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

