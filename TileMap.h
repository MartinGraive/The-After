/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#pragma once

#include "Graphics/Drawable.h"
#include "Graphics/TextureHandler.h"
#include "Tile.h"

class TileMap : public Drawable
{
    public:
        int prepare(Texture s, std::vector<std::vector<Tile> > tiles, const unsigned int width, const unsigned int height);
};

