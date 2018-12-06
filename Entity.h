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
#include "RenderingArray.h"
#include "Settings.h"

class Entity //Abstract class for every item / object / character
{
    public:
        Entity(RenderingArray* a = NULL);
        virtual ~Entity();

        virtual void draw(sf::RenderWindow* window);
        virtual void drawAbove(sf::RenderWindow* window);

        ///Process
        virtual void process();

        void setX(double i);
        void setY(double i, bool ordering = true);
        void setRenderingOrder(int i);
        double getX() const;
        double getY() const;
        double getXbase() const;
        double getYbase() const;
        Rect getBaseRect() const;
        bool isSolid() const;
        virtual EntityType getType() const;

        ///SELECTION
        virtual void move(int xt, int yt);
    protected:
        double x;
        double y;
        int w;
        int h;
        bool solid;
        sf::Clock clock;
        TypeAnim typeanim;
        int anim;
        Rect baseRect;

        int renderingOrder;
        RenderingArray* array;
};
