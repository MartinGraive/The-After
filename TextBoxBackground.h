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
#include "Tile.h"

class TextBoxBackground : public Drawable
{
    public:
        int prepare(Texture t, const unsigned int width, const unsigned int height);
};


