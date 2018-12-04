/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#ifndef DEF_GRAPHICS
#define DEF_GRAPHICS
#include <SFML/Graphics.hpp>
#include "TextureHandler.h"

class Graphics
{
    public:
        static Graphics* getInstance();
        void drawSprite(sf::RenderWindow* win, Texture t, int px, int py, int cx = -1, int cy = -1, int cw = -1, int ch = -1, double scale = 1);
        void drawEllipse(sf::RenderWindow* win, int px, int py, double w, double h, double scale = 1, int alpha = 255);
    private:
        Graphics();
        ~Graphics();
        static Graphics* instance;
};

#endif // DEF_TEXTUREHANDLER

