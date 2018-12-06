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
#include "TextureHandler.h"

class Drawable : public sf::Drawable, public sf::Transformable
{
    protected:
        sf::VertexArray vertices;
        sf::Texture source;
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            states.transform *= getTransform();

            states.texture = &source;

            target.draw(vertices, states);
        }
};

