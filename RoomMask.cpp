/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include "Settings.h"
#include "Graphics/TextureHandler.h"
#include "Graphics/Graphics.h"
#include "RoomMask.h"

int RoomMask::prepare(Texture t, const unsigned int width, const unsigned int height, Rect room)
{
    w = width;
    h = height;
    source = *t.t;

    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(4 * 4);

    int tu = 64, tv = 160, tw = TILE_SIZE, th = TILE_SIZE;
    int xs = 0, ys = 0, ws = w, hs = room.y * TILE_SIZE;
    for (int i = 0 ; i < 4 ; i++) {
        if (i == 1) {
            xs = (room.x + room.w) * TILE_SIZE, ys = room.y * TILE_SIZE, ws = w - xs, hs = h - ys;
        }
        else if (i == 2) {
            xs = 0, ys = (room.y + room.h) * TILE_SIZE - TILE_SIZE / 2, ws = (room.x + room.w) * TILE_SIZE, hs = h - ys;
        }
        else if (i == 3) {
            xs = 0, ys = room.y * TILE_SIZE, ws = room.x * TILE_SIZE, hs = room.h * TILE_SIZE - TILE_SIZE / 2;
        }
        vertices[i * 4].position = sf::Vector2f(xs, ys);
        vertices[i * 4 + 1].position = sf::Vector2f(xs + ws, ys);
        vertices[i * 4 + 2].position = sf::Vector2f(xs + ws, ys + hs);
        vertices[i * 4 + 3].position = sf::Vector2f(xs, ys + hs);
        vertices[i * 4].texCoords = sf::Vector2f(tu, tv);
        vertices[i * 4 + 1].texCoords = sf::Vector2f(tu + tw, tv);
        vertices[i * 4 + 2].texCoords = sf::Vector2f(tu + tw, tv + th);
        vertices[i * 4 + 3].texCoords = sf::Vector2f(tu, tv + th);
    }

    return true;
}

unsigned int RoomMask::getWidth()
    { return w; }

unsigned int RoomMask::getHeight()
    { return h; }

void RoomMask::setFillColor(sf::Color c)
{
    for (unsigned int i = 0 ; i < vertices.getVertexCount() ; i++) {
        vertices[i].color = c;
    }
}
