/*THE AFTER
Commenc� le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include "GameCore.h"
#include "TileMap.h"
#include "Map.h"
#include "Settings.h"
#include "Graphics/TextureHandler.h"
#include "Graphics/Graphics.h"

int TileMap::prepare(const std::string& tileset_file, std::vector<std::vector<Tile> > tiles, const unsigned int width, const unsigned int height)
{
    if (!loadSource(tileset_file)) {
        return false;
    }

    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(width * height * 4);

    for (unsigned int i = 0 ; i < width ; i++) {
        for (unsigned int j = 0 ; j < height ; j++) {
            int tu = tiles[i][j].getTexCoords().x;
            int tv = tiles[i][j].getTexCoords().y;

            sf::Vertex* quad = &vertices[(i + j * width) * 4];

            quad[0].position = sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE);
            quad[1].position = sf::Vector2f((i+1) * TILE_SIZE, j * TILE_SIZE);
            quad[2].position = sf::Vector2f((i+1) * TILE_SIZE, (j+1) * TILE_SIZE);
            quad[3].position = sf::Vector2f(i * TILE_SIZE, (j+1) * TILE_SIZE);
            quad[0].texCoords = sf::Vector2f(tu * TILE_SIZE, tv * TILE_SIZE);
            quad[1].texCoords = sf::Vector2f((tu+1) * TILE_SIZE, tv * TILE_SIZE);
            quad[2].texCoords = sf::Vector2f((tu+1) * TILE_SIZE, (tv+1) * TILE_SIZE);
            quad[3].texCoords = sf::Vector2f(tu * TILE_SIZE, (tv+1) * TILE_SIZE);
        }
    }
    return true;
}
