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
        TextBox(std::string t, int x1, int y1, int wmax1, Entity* track = NULL);
        void prepare(std::string t, int x1, int y1, int wmax1);
        ~TextBox();

        void draw(sf::RenderWindow* window);
    private:
        std::string splitText(std::string s, std::vector<std::string> words, std::vector<int> lengths);

        int x;
        int y;
        int wmax;
        std::string text;
        sf::Text textTexture;
        Entity* trackTarget;
        TextBoxBackground bubble;
};

