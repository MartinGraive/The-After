/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#pragma once

#include "TextBoxBackground.h"

class TextBox
{
    public:
        TextBox(std::string t, int x1, int y1);
        ~TextBox();

        void draw(sf::RenderWindow* window);
    private:
        int x;
        int y;
        std::string text;
        sf::Text textTexture;
        TextBoxBackground bubble;
};

