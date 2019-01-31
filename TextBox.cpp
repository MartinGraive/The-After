/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include <cmath>
#include "TextBox.h"
#include "Graphics/FontHandler.h"
#include "Primitives/StringPrimitives.h"

TextBox::TextBox(std::wstring t, int x1, int y1, int wmax1, Entity* track) : x(x1), y(y1), wmax(wmax1), text(t), trackTarget(track)
{
    prepare(t, x, y, wmax);
}

TextBox::~TextBox()
{
}

void TextBox::prepare(std::wstring t, int x1, int y1, int wmax1)
{
    x = x1; y = y1; wmax = wmax1; text = t;
    std::vector<std::wstring> wordsString = StringPrimitives::split(text, ' ', true, 30);
    std::vector<int> wordLengths;
    for (unsigned int i = 0 ; i < wordsString.size() ; i++) {
        sf::Text texte;
        texte.setFont(*FontHandler::getInstance()->getFont());
        texte.setString(wordsString[i]);
        texte.setCharacterSize(12);
        wordLengths.push_back(texte.getLocalBounds().width);
    }
    text = splitText(text, wordsString, wordLengths);

    textTexture.setFont(*FontHandler::getInstance()->getFont());
    textTexture.setString(text);
    textTexture.setCharacterSize(12);
    textTexture.setFillColor(sf::Color::Black);

    int bubble_width = textTexture.getLocalBounds().width + 15, bubble_height = textTexture.getLocalBounds().height + 12;
    bubble_width = ceil((bubble_width - 12) / 8) * 8 + 12;
    bubble_height = ceil((bubble_height - 12) / 4) * 4 + 12;
    bubble.prepare(TextureHandler::getInstance()->getBubble(), bubble_width, bubble_height);

    std::wcout<<"Text="<<text<<" height="<<textTexture.getLocalBounds().height<<" bulle="<<bubble_height<<"\n";
}

/**
  * Add \n in text so it never goes out of the box
  **/
std::wstring TextBox::splitText(std::wstring s, std::vector<std::wstring> words, std::vector<int> lengths)
{
    int actual_width = 0;
    int actual_position = 0;
    for (unsigned int i = 0 ; i < lengths.size() ; i++) {
        actual_width += lengths[i];
        if (actual_width > wmax - 10 && actual_width - lengths[i] > 0) {
            s[actual_position - 1] = '\n';
            actual_width = 0;
        }
        actual_position += words[i].size();
    }

    return s;
}

void TextBox::draw(sf::RenderWindow* window)
{
    if (trackTarget != NULL) {
        x = trackTarget->getX() + trackTarget->getBaseRect().x + trackTarget->getBaseRect().w / 2;
        y = trackTarget->getY() - 1;
    }
    // (x,y) represents the edge of the arrow
    int xdraw = x - bubble.getWidth() / 2, ydraw = y - bubble.getHeight();
    bubble.setPosition(xdraw, ydraw);
    window->draw(bubble);

    textTexture.setPosition(xdraw + (bubble.getWidth() - textTexture.getLocalBounds().width) / 2, ydraw + (bubble.getHeight() - 2 - textTexture.getLocalBounds().height - textTexture.getLocalBounds().top) / 2);
    window->draw(textTexture);
}
