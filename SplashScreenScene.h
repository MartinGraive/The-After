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

class SplashScreenScene : public AbstractScene
{
    public:
        SplashScreenScene(sf:: RenderWindow* window);
        ~SplashScreenScene();

        void draw();
        void process();
    private:
        sf::RenderWindow* window;

        int frameElapsed;

        Texture ki;
};

