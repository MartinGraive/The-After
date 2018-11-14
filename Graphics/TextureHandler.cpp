/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

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
    chara1 = loadTexture(Settings::getInstance()->getPath()+"data/graphics/chara/chara1.png");
    tiles = loadTexture(Settings::getInstance()->getPath()+"data/graphics/tiles/Basis.png");
}

sf::Texture* TextureHandler::loadTexture(std::string src)
{
    sf::Texture* tex = new sf::Texture;
    sf::Image img;
    if (img.loadFromFile(src)) {
        img.createMaskFromColor(img.getPixel(img.getSize().x-1,0),0);
        tex->loadFromImage(img);
    }

    return tex;
}

void TextureHandler::freeGame()
{
    delete chara1;
    delete tiles;
}

sf::Texture* TextureHandler::getChara1()
    { return chara1; }

sf::Texture* TextureHandler::getTiles()
    { return tiles; }
