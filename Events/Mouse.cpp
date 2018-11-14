/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include "Mouse.h"
#include "Events.h"
#include "../GameCore.h"

Mouse::Mouse() : leftPressed(false), rightPressed(false)
{
}

Mouse::~Mouse()
{
}

void Mouse::handleMouse()
{
    /// LEFT CLIC
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !leftPressed) {
        leftPressed = true;
    }
    else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && leftPressed) {
        leftPressed = false;
    }

    /// RIGHT CLIC
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !rightPressed) {
        rightPressed = true;
    }
    else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right) && rightPressed) {
        rightPressed = false;
    }
}

void Mouse::pressLeft(int x, int y)
{
    ///PLACES SELECTION
}

void Mouse::pressRight(int x, int y)
{
}

void Mouse::releaseLeft(int x, int y)
{
}

void Mouse::releaseRight(int x, int y)
{
}

void Mouse::motion(int x, int y)
{
    if (leftPressed) {
    }
}
