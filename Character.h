/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Graphics/TextureHandler.h"
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
        void move(double xt, double yt);
        bool collideWithEntities(double xd, double yd);
        void setTypeAnim(TypeAnim t);

        double getSpeed() const;
    protected:
        void drawStillAndMove(sf::RenderWindow* window);

        int direction;
        double speed;
        Texture tex;
};
