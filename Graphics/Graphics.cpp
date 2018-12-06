/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include "Graphics.h"
#include "../Primitives/EllipseShape.h"
#include "../Settings.h"
#include "../Camera.h"

Graphics* Graphics::instance = new Graphics;

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

Graphics* Graphics::getInstance() { return instance; }

void Graphics::drawSprite(sf::RenderWindow* win, Texture t, int px, int py, int cx, int cy, int cw, int ch, double scale)
{
    sf::Sprite sprite(*t.t);
    sprite.setTextureRect(sf::IntRect(cx, cy, cw, ch));

    sprite.setPosition(px, py);
    win->draw(sprite);
}

void Graphics::drawEllipse(sf::RenderWindow* win, int px, int py, double w, double h, double scale, int alpha)
{
    EllipseShape shadow(sf::Vector2f(w,h));
    shadow.setFillColor(sf::Color(0,0,0,alpha));
    ///SCALLING
    shadow.setScale(scale, scale);

    shadow.setPosition(px, py);
    win->draw(shadow);
}
