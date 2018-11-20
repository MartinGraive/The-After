/*THE AFTER
Commenc� le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#pragma once

#include <SFML/Graphics.hpp>

class Drawable : public sf::Drawable, public sf::Transformable
{
    protected:
        bool loadSource(std::string filename) {
            if (!source.loadFromFile(filename)) {
                return false;
            }
            return true;
        }
        sf::VertexArray vertices;
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            states.transform *= getTransform();

            states.texture = &source;

            target.draw(vertices, states);
        }
        sf::Texture source;
};

