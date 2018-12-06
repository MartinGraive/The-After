/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include "TextBox.h"
#include "Graphics/FontHandler.h"

TextBox::TextBox(std::string t, int x1, int y1) : x(x1), y(y1), text(t)
{
    textTexture.setFont(*FontHandler::getInstance()->getFont());
    textTexture.setString(t);
    textTexture.setCharacterSize(14);
    textTexture.setFillColor(sf::Color::Black);
    bubble.prepare(TextureHandler::getInstance()->getBubble(), 12 + 8*4, 12 + 4*2);
}

TextBox::~TextBox()
{
}

void TextBox::draw(sf::RenderWindow* window)
{
    bubble.setPosition(x, y);
    window->draw(bubble);

    textTexture.setPosition(x + 4, y + 2);
    window->draw(textTexture);
}
