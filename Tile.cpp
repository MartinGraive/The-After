/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include "GameCore.h"
#include "Tile.h"
#include "Map.h"
#include "Settings.h"
#include "Graphics/TextureHandler.h"
#include "Graphics/Graphics.h"

Tile::Tile() : solid(false)
{
    corner[0] = corner[1] = corner[2] = corner[3] = false;
}

Tile::~Tile()
{
}

void Tile::draw(sf::RenderWindow* window)
{
    drawCouche1(window);
    drawCouche2(window);
}

void Tile::drawCouche1(sf::RenderWindow* window)
{
    int xt = c1 % 30;
    int yt = (int)(c1 / 30);
    if (c1 == EAU) { xt += map->getAnim(); }
    Graphics::getInstance()->drawSprite(window, TextureHandler::getInstance()->getTiles(),
                                        x*TILE_SIZE, y*TILE_SIZE, xt*TILE_SIZE, yt*TILE_SIZE, TILE_SIZE, TILE_SIZE);
}

void Tile::drawCouche2(sf::RenderWindow* window)
{
    int xt = c2 % 30;
    int yt = (int)(c2 / 30);
    Graphics::getInstance()->drawSprite(window, TextureHandler::getInstance()->getTiles(),
                                        x*TILE_SIZE, y*TILE_SIZE, xt*TILE_SIZE, yt*TILE_SIZE, TILE_SIZE, TILE_SIZE);

    ///CORNERS autotiles
    if (corner[LU]) {
        Graphics::getInstance()->drawSprite(window, TextureHandler::getInstance()->getTiles(),
                                            x*TILE_SIZE, y*TILE_SIZE, 64, 16, 4, 4);
    }
    if (corner[LD]) {
        Graphics::getInstance()->drawSprite(window, TextureHandler::getInstance()->getTiles(),
                                            x*TILE_SIZE, y*TILE_SIZE+12, 64, 12, 4, 4);
    }
    if (corner[RU]) {
        Graphics::getInstance()->drawSprite(window, TextureHandler::getInstance()->getTiles(),
                                            x*TILE_SIZE+12, y*TILE_SIZE, 60, 16, 4, 4);
    }
    if (corner[RD]) {
        Graphics::getInstance()->drawSprite(window, TextureHandler::getInstance()->getTiles(),
                                            x*TILE_SIZE+12, y*TILE_SIZE+12, 60, 12, 4, 4);
    }
}

void Tile::init()
{
    if (c1 == EAU || c2 == MONTAGNE) {
        solid = true;
    }
}

void Tile::setPos(int i, int j)
    { x = i; y = j; }

void Tile::setCouches(int co1, int co2)
    { c1 = co1; c2 = co2; init(); }

int Tile::getC1() const
    { return c1; }

int Tile::getC2() const
    { return c2; }

void Tile::setCorner(bool val, int i)
    { corner[i] = val; }

void Tile::setMap(Map* i)
    { map = i; }

bool Tile::isSolid() const
    { return solid; }
