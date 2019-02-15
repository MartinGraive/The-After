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
#include <string>

class HUD
{
    public:
        HUD();
        ~HUD();

        void draw(sf::RenderWindow* window);
    private:
        void drawStars(sf::RenderWindow* window);
        void drawChrono(sf::RenderWindow* window);
        std::string formatTime(int frames);
        std::string formatNumber(int num);
};
