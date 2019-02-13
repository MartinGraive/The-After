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
#include "Graphics/TextureHandler.h"

class TitleScene : public AbstractScene
{
    public:
        TitleScene(sf:: RenderWindow* window);
        ~TitleScene();

        void draw();
        void process();

        int getType();
    private:
        sf::RenderWindow* window;

        Texture title;
        Texture background;
};


