/*THE AFTER
Commenc� le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include "GameCore.h"
#include "Tile.h"
#include "Map.h"
#include "Settings.h"
#include "Graphics/TextureHandler.h"
#include "Graphics/Graphics.h"

Tile::Tile() : halftex(-1), halfhorizontal(false), solid(false)
{
    corner[0] = corner[1] = corner[2] = corner[3] = false;
}

Tile::~Tile()
{
}

Point Tile::getTexCoords() const
{
    int xt = (tex % TILESET_WIDTH) * TILE_SIZE;
    int yt = (tex / TILESET_WIDTH) * TILE_SIZE;

    return Point(xt, yt);
}

Point Tile::getSecondaryTexCoords() const
{
    int xt = (halftex % TILESET_WIDTH) * TILE_SIZE;
    int yt = (halftex / TILESET_WIDTH) * TILE_SIZE;

    return Point(xt, yt);
}

void Tile::init()
{
}

void Tile::setPos(int i, int j)
    { x = i; y = j; }

void Tile::setVal(int i)
    { val = i; tex = i; }

void Tile::setTex(int i)
    { tex = i; }

void Tile::setHalfTex(int i)
    { halftex = i; }

void Tile::setHalfHorizontal(bool i)
    { halfhorizontal = i; }

bool Tile::isHalfHorizontal() const
    { return halfhorizontal; }

int Tile::getVal() const
    { return val; }

int Tile::getTex() const
    { return tex; }

int Tile::getHalfTex() const
    { return halftex; }

void Tile::setCorner(bool val, int i)
    { corner[i] = val; }

void Tile::setMap(Map* i)
    { map = i; }

bool Tile::isSolid() const
    { return solid; }

bool Tile::getCorner(int i) const
    { return corner[i]; }
