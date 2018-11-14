/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

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
            if (event.mouseButton.button == sf::Mouse::Left) {
                mouse->pressLeft(event.mouseButton.x, event.mouseButton.y);
            }
            else if (event.mouseButton.button == sf::Mouse::Right) {
                mouse->pressRight(event.mouseButton.x, event.mouseButton.y);
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                mouse->releaseLeft(event.mouseButton.x, event.mouseButton.y);
            }
            else if (event.mouseButton.button == sf::Mouse::Right) {
                mouse->releaseRight(event.mouseButton.x, event.mouseButton.y);
            }
        }
        else if (event.type == sf::Event::MouseMoved) {
            mouse->motion(event.mouseMove.x, event.mouseMove.y);
        }
    }
    mouse->handleMouse();
    key->handleKeys();
}

sf::Event Events::getEvent()
    { return event; }
