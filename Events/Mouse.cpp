/*THE AFTER
Commenc� le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include "Mouse.h"
#include "Events.h"
#include "../SceneManager.h"
#include "../GameScene.h"
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
    if (SceneManager::getInstance()->top()->getType() == TITLE) {
        if (x >= 321 && y >= 504 && x <= 459 && y <= 555) {
            GameScene* scene = new GameScene(SceneManager::getInstance()->getWindow());
            SceneManager::getInstance()->stackScene(scene);
        }
        else if (x >= 682 && y >= 501 && x <= 855 && y <= 557) {
            SceneManager::getInstance()->popScene();
        }
    }
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
