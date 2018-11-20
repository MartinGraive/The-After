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

Tile::Tile() : solid(false)
{
    corner[0] = corner[1] = corner[2] = corner[3] = false;
}

Tile::~Tile()
{
}

Point Tile::getTexCoords()
{
    int xt = val % TILESET_WIDTH;
    int yt = val / TILESET_WIDTH;

    return Point(xt, yt);
}

void Tile::init()
{
}

void Tile::setPos(int i, int j)
    { x = i; y = j; }

void Tile::setVal(int i)
    { val = i; }

int Tile::getVal() const
    { return val; }

void Tile::setCorner(bool val, int i)
    { corner[i] = val; }

void Tile::setMap(Map* i)
    { map = i; }

bool Tile::isSolid() const
    { return solid; }
