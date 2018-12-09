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
#include "TextBoxBackground.h"

int TextBoxBackground::prepare(Texture t, const unsigned int width, const unsigned int height)
{
    w = width;
    h = height;
    source = *t.t;

    //structure
    // 6*6 + width*6 + 6*6
    // 6*height + width*height + 6*height
    // 6*6 + width*6 + 6*6

    const int corner_size = 6;

    const int unit_bit = 4;

    vertices.setPrimitiveType(sf::Quads);
    vertices.resize((2 + width / unit_bit) * (2 + height / unit_bit) * 4);

    for (unsigned int i = 0 ; i < 4 ; i++) { //corners
        int j = 0;
        if (i == 1) { j = width / unit_bit - 1; }
        else if (i == 2) { j = (height / unit_bit - 1) * (width / unit_bit); }
        else if (i == 3) { j = height / unit_bit * width / unit_bit - 1; }
        int posx = 0, posy = 0;
        int tu = 0, tv = 0;
        int tw = corner_size, th = corner_size;
        if (i == 1 || i == 2) {
            posx = width - corner_size;
            tu = 21;
        }
        if (i == 2 || i == 3) {
            posy = height - corner_size;
            tv = 13;
            th = corner_size + 1;
        }
        vertices[j * 4].position = sf::Vector2f(posx, posy);
        vertices[j * 4 + 1].position = sf::Vector2f(posx + tw, posy);
        vertices[j * 4 + 2].position = sf::Vector2f(posx + tw, posy + th);
        vertices[j * 4 + 3].position = sf::Vector2f(posx, posy + th);
        vertices[j * 4].texCoords = sf::Vector2f(tu, tv);
        vertices[j * 4 + 1].texCoords = sf::Vector2f(tu + tw, tv);
        vertices[j * 4 + 2].texCoords = sf::Vector2f(tu + tw, tv + th);
        vertices[j * 4 + 3].texCoords = sf::Vector2f(tu, tv + th);
    }
    unsigned int wloop = (width - corner_size + unit_bit) / unit_bit;
    unsigned int hloop = (height - corner_size + unit_bit) / unit_bit;
    for (unsigned int i = 0 ; i < wloop ; i++) {
        for (unsigned int j = 0 ; j < hloop ; j++) {
            if ((i != 0 || j != 0) && (i != wloop - 1 || j != 0) && (i != wloop - 1 || j != hloop - 1) && (i != 0 || j != hloop - 1)) {
                int tu = 11, tv = 8;
                int tw = unit_bit, th = unit_bit;
                int posx = corner_size + unit_bit * (i - 1), posy = corner_size + unit_bit * (j - 1);
                if (j == 0) {
                    posy = 0;
                    tv = 0;
                    th = corner_size;
                }
                else if (j == hloop - 1) {
                    if (i == wloop / 2 - 1) {
                        tu = 9;
                        tv = 13;
                        th = 15;
                    }
                    else if (i == wloop / 2) {
                        tu = 13;
                        tv = 13;
                        th = 15;
                    }
                    else {
                        tu = 17;
                        tv = 13;
                        th = corner_size + 1;
                    }
                }
                if (i == 0) {
                    posx = 0;
                    tu = 0;
                    tw = corner_size;
                }
                else if (i == wloop - 1) {
                    tu = 21;
                    tw = corner_size;
                }
                sf::Vertex* quad = &vertices[(i + j * width / unit_bit) * 4];

                quad[0].position = sf::Vector2f(posx, posy);
                quad[1].position = sf::Vector2f(posx + tw, posy);
                quad[2].position = sf::Vector2f(posx + tw, posy + th);
                quad[3].position = sf::Vector2f(posx, posy + th);
                quad[0].texCoords = sf::Vector2f(tu, tv);
                quad[1].texCoords = sf::Vector2f(tu + tw, tv);
                quad[2].texCoords = sf::Vector2f(tu + tw, tv + th);
                quad[3].texCoords = sf::Vector2f(tu, tv + th);
            }
        }
    }
    return true;
}

unsigned int TextBoxBackground::getWidth()
    { return w; }

unsigned int TextBoxBackground::getHeight()
    { return h; }
