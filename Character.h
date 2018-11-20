/*THE AFTER
Commenc� le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "RenderingArray.h"
#include "Settings.h"
#include "Entity.h"

class Character : public Entity //Abstract class for every character
{
    public:
        Character(RenderingArray* a = NULL);
        ~Character();

        void process();
        void draw(sf::RenderWindow* window);
        EntityType getType() const;
        bool collideWithEntities(double xd, double yd);
        void setTypeAnim(TypeAnim t);

        double getSpeed() const;
    protected:
        void drawStillAndMove(sf::RenderWindow* window);

        int direction;
        double speed;
};
