/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include "FontHandler.h"
#include "../Settings.h"

FontHandler* FontHandler::instance = NULL;

FontHandler::FontHandler()
{
}

FontHandler::~FontHandler()
{
    delete font;
}

FontHandler* FontHandler::getInstance() { return instance; }

void FontHandler::createInstance()
{
    instance = new FontHandler;
    instance->loadFonts();
}

void FontHandler::loadFonts()
{
    font = new sf::Font;
    font->loadFromFile(Settings::getInstance()->getPath()+"data/graphics/fonts/arial.ttf");
}

sf::Font* FontHandler::getFont()
    { return font; }

