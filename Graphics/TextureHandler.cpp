/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include <sstream>
#include "TextureHandler.h"
#include "../Settings.h"

TextureHandler* TextureHandler::instance = new TextureHandler;

TextureHandler::TextureHandler()
{
}

TextureHandler::~TextureHandler()
{
}

TextureHandler* TextureHandler::getInstance() { return instance; }

void TextureHandler::loadGame()
{
    for (int i = 0 ; i < NB_CHARAS ; i++) {
        std::ostringstream im;
        im << i + 1;
        charas[i] = loadTexture(Settings::getInstance()->getPath()+"data/graphics/chara/chara"+im.str()+".png");
    }
    vigils[0] = loadTexture(Settings::getInstance()->getPath()+"data/graphics/chara/vigil.png");
    tileset = loadTexture(Settings::getInstance()->getPath()+"data/graphics/tiles/chipset.png");
    bubble = loadTexture(Settings::getInstance()->getPath()+"data/graphics/system/bubble.png");
    stars = loadTexture(Settings::getInstance()->getPath()+"data/graphics/system/stars.png");
    weisted = loadTexture(Settings::getInstance()->getPath()+"data/graphics/system/weisted.png");
}

Texture TextureHandler::loadTexture(std::string src)
{
    sf::Texture* tex = new sf::Texture;
    sf::Image img;
    if (img.loadFromFile(src)) {
        img.createMaskFromColor(img.getPixel(img.getSize().x-1,0),0);
        tex->loadFromImage(img);
    }
    Texture t;
    t.t = tex;
    t.w = img.getSize().x;
    t.h = img.getSize().y;
    return t;
}

void TextureHandler::freeGame()
{
    delete charas[0].t;
    delete vigils[0].t;
    delete tileset.t;
    delete bubble.t;
    delete stars.t;
    delete weisted.t;
}

Texture TextureHandler::getCharas(int i)
    { return charas[i]; }

Texture TextureHandler::getVigils(int i)
    { return vigils[i]; }

Texture TextureHandler::getTileset()
    { return tileset; }

Texture TextureHandler::getBubble()
    { return bubble; }

Texture TextureHandler::getStars()
    { return stars; }

Texture TextureHandler::getWeisted()
    { return weisted; }
