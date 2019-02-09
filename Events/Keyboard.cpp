/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
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
}

void Keyboard::punctualPress()
{
    if (events->getEvent().key.code == sf::Keyboard::Space) {
        RenderingArray* r = GameCore::getInstance()->getEntities();
        MainPlayer* m = GameCore::getInstance()->getMPlayer();
        for (int i = 0 ; i < r->size() ; i++) {
            Entity* e = r->getEntity(i);
            int range = 4;
            if (m->getDirection() == HAUT) {
                if (m->getXbase() < e->getXbase() + e->getBaseRect().w && m->getXbase() + m->getBaseRect().w > e->getXbase() &&
                    m->getYbase() - range < e->getYbase() + e->getBaseRect().h && m->getYbase() > e->getYbase()) {
                    e->activate();
                }
            }
            else if (m->getDirection() == BAS) {
                if (m->getXbase() < e->getXbase() + e->getBaseRect().w && m->getXbase() + m->getBaseRect().w > e->getXbase() &&
                    m->getYbase() + m->getBaseRect().h < e->getYbase() + e->getBaseRect().h && m->getYbase() + m->getBaseRect().h + range > e->getYbase()) {
                    e->activate();
                }
            }
            else if (m->getDirection() == GAUCHE) {
                if (m->getYbase() < e->getYbase() + e->getBaseRect().h && m->getYbase() + m->getBaseRect().h > e->getYbase() &&
                    m->getXbase() - range < e->getXbase() + e->getBaseRect().w && m->getXbase() > e->getXbase()) {
                    e->activate();
                }
            }
            else if (m->getDirection() == DROITE) {
                if (m->getYbase() < e->getYbase() + e->getBaseRect().h && m->getYbase() + m->getBaseRect().h > e->getYbase() &&
                    m->getXbase() + m->getBaseRect().w < e->getXbase() + e->getBaseRect().w && m->getXbase() + m->getBaseRect().w + range > e->getXbase()) {
                    e->activate();
                }
            }
        }
    }
}

