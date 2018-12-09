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
#include "Entity.h"

class TextBox
{
    public:
        TextBox(std::wstring t, int x1, int y1, int wmax1, Entity* track = NULL);
        void prepare(std::wstring t, int x1, int y1, int wmax1);
        ~TextBox();

        void draw(sf::RenderWindow* window);
    private:
        std::wstring splitText(std::wstring s, std::vector<std::wstring> words, std::vector<int> lengths);

        int x;
        int y;
        int wmax;
        std::wstring text;
        sf::Text textTexture;
        Entity* trackTarget;
        TextBoxBackground bubble;
};

