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
    vertices.resize(width * height * 4 * 4);

    for (unsigned int i = 0 ; i < width ; i++) {
        for (unsigned int j = 0 ; j < height ; j++) {
            int tu = tiles[i][j].getTexCoords().x;
            int tv = tiles[i][j].getTexCoords().y;

            sf::Vertex* quad = &vertices[(i + j * width) * 4 * 4];

            for (int k = 0 ; k < 4 ; k++) { // a tile is composed of 4 sub tiles
                tu = tiles[i][j].getTexCoords().x;
                tv = tiles[i][j].getTexCoords().y;
                int xadd = 0, yadd = 0;
                if (k == 1) {
                    xadd = TILE_SIZE / 2;
                    if (tiles[i][j].getHalfTex() > -1 && tiles[i][j].isHalfHorizontal()) {
                        tu = tiles[i][j].getSecondaryTexCoords().x;
                        tv = tiles[i][j].getSecondaryTexCoords().y;
                    }
                }
                else if (k == 2) {
                    yadd = TILE_SIZE / 2;
                    if (tiles[i][j].getHalfTex() > -1 && !tiles[i][j].isHalfHorizontal()) {
                        tu = tiles[i][j].getSecondaryTexCoords().x;
                        tv = tiles[i][j].getSecondaryTexCoords().y;
                    }
                }
                else if (k == 3) {
                    xadd = TILE_SIZE / 2;
                    yadd = TILE_SIZE / 2;
                    if (tiles[i][j].getHalfTex() > -1) {
                        tu = tiles[i][j].getSecondaryTexCoords().x;
                        tv = tiles[i][j].getSecondaryTexCoords().y;
                    }
                }
                if (tiles[i][j].getCorner(k)) {
                    int val = tiles[i][j].getVal() - 2 * TILESET_WIDTH + 1;
                    tu = (val % TILESET_WIDTH) * TILE_SIZE;
                    tv = (val / TILESET_WIDTH) * TILE_SIZE;
                }
                quad[0 + k * 4].position = sf::Vector2f(i * TILE_SIZE + xadd, j * TILE_SIZE + yadd);
                quad[1 + k * 4].position = sf::Vector2f(i * TILE_SIZE + TILE_SIZE / 2 + xadd, j * TILE_SIZE + yadd);
                quad[2 + k * 4].position = sf::Vector2f(i * TILE_SIZE + TILE_SIZE / 2 + xadd, j * TILE_SIZE + TILE_SIZE / 2 + yadd);
                quad[3 + k * 4].position = sf::Vector2f(i * TILE_SIZE + xadd, j * TILE_SIZE + TILE_SIZE / 2 + yadd);
                quad[0 + k * 4].texCoords = sf::Vector2f(tu + xadd, tv + yadd);
                quad[1 + k * 4].texCoords = sf::Vector2f(tu + TILE_SIZE / 2 + xadd, tv + yadd);
                quad[2 + k * 4].texCoords = sf::Vector2f(tu + TILE_SIZE / 2 + xadd, tv + TILE_SIZE / 2 + yadd);
                quad[3 + k * 4].texCoords = sf::Vector2f(tu + xadd, tv + TILE_SIZE / 2 + yadd);
            }
        }
    }
    return true;
}
