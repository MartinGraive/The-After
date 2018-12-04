/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "RenderingArray.h"
#include "Settings.h"
#include "Character.h"

class Vigil : public Character
{
    public:
        Vigil(Texture t, RenderingArray* a = NULL);
        ~Vigil();
};

