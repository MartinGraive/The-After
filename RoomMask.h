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
#include "Settings.h"

class RoomMask : public Drawable
{
    public:
        int prepare(Texture t, const unsigned int width, const unsigned int height, Rect rect);
        unsigned int getWidth();
        unsigned int getHeight();
        void setFillColor(sf::Color c);
    private:
        unsigned int w;
        unsigned int h;
};
