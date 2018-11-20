/*THE AFTER
Commenc� le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#pragma once

#include "Graphics/Drawable.h"
#include "Tile.h"

class TileMap : public Drawable
{
    public:
        int prepare(const std::string& tileset_file, std::vector<std::vector<Tile> > tiles, const unsigned int width, const unsigned int height);
};

