/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include "Keyboard.h"
#include "Events.h"
#include "../GameCore.h"
#include "../Settings.h"

Keyboard::Keyboard(Events* ev) : events(ev)
{
}

Keyboard::~Keyboard()
{
}

void Keyboard::handleKeys()
{
    double xt = 0, yt = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        xt=-GameCore::getInstance()->getMPlayer()->getSpeed();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        xt=+GameCore::getInstance()->getMPlayer()->getSpeed();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        yt=-GameCore::getInstance()->getMPlayer()->getSpeed();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        yt=+GameCore::getInstance()->getMPlayer()->getSpeed();
    }
    if (xt != 0 || yt != 0) {
        GameCore::getInstance()->getMPlayer()->move(xt,yt);
    }
    else {GameCore::getInstance()->getMPlayer()->setTypeAnim(STILL);}
}

void Keyboard::punctualPress()
{
    switch (events->getEvent().key.code)
    {
        default:
            break;
    }
}

