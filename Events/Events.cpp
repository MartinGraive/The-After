/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include "Events.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "../Settings.h"

Events* Events::instance = new Events;

Events::Events()
{
    key = new Keyboard(this);
    mouse = new Mouse;
}

Events::~Events()
{
    delete mouse;
    delete key;
}

Events* Events::getInstance() { return instance; }

void Events::handleEvents(sf::RenderWindow* window)
{
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            Settings::getInstance()->quit();
        }
        else if (event.type == sf::Event::KeyPressed) {
            key->punctualPress();
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            Point p = getRealMouseCoordinates(event.mouseButton.x, event.mouseButton.y, window);
            if (event.mouseButton.button == sf::Mouse::Left) {
                mouse->pressLeft(p.x, p.y);
            }
            else if (event.mouseButton.button == sf::Mouse::Right) {
                mouse->pressRight(p.x, p.y);
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            Point p = getRealMouseCoordinates(event.mouseButton.x, event.mouseButton.y, window);
            if (event.mouseButton.button == sf::Mouse::Left) {
                mouse->releaseLeft(p.x, p.y);
            }
            else if (event.mouseButton.button == sf::Mouse::Right) {
                mouse->releaseRight(p.x, p.y);
            }
        }
        else if (event.type == sf::Event::MouseMoved) {
            Point p = getRealMouseCoordinates(event.mouseMove.x, event.mouseMove.y, window);
            mouse->motion(p.x, p.y);
        }
    }
    mouse->handleMouse();
    key->handleKeys();
}

sf::Event Events::getEvent()
    { return event; }

Point Events::getRealMouseCoordinates(int x, int y, sf::RenderWindow* window)
{
    Point p;
    p.x = x * Settings::getInstance()->getW() / window->getSize().x;
    p.y = y * Settings::getInstance()->getH() / window->getSize().y;
    return p;
}
