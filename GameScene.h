/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#pragma once

#include <SFML/Graphics.hpp>
#include "AbstractScene.h"

class GameScene : public AbstractScene
{
    public:
        GameScene(sf:: RenderWindow* window);

        void draw();
        void process();
    private:
        void drawEntities();

        sf::RenderWindow* window;
};
