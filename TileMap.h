/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse

Projet de TDLog*/

#pragma once

#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
    public:
        TileMap();

        int prepare(const std::string& tileset_file, const int* tiles, const unsigned int width, const unsigned int height);
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            states.transform *= getTransform();

            states.texture = &tileset;

            target.draw(vertices, states);
        }

        sf::VertexArray vertices;
        sf::Texture tileset;
};

