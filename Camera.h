/*THE AFTER
Commenc� le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Camera
{
    public:
        Camera(sf::RenderWindow* win);

        int getPhg(int i) const;
        void scrollScreen(int x, int y);
        void autoScroll();

        void reset();
    private:
        void process();

        int phg[2];
        sf::View view;
        sf::RenderWindow* window;
};


