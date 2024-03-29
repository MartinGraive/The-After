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
#include "TextBox.h"

#define MAX_FRAME_BUBBLE 300

class Character : public Entity //Abstract class for every character
{
    public:
        Character(RenderingArray* a = NULL);
        ~Character();

        virtual void process();
        void draw(sf::RenderWindow* window);
        void drawAbove(sf::RenderWindow* window);
        EntityType getType() const;
        void move(double xt, double yt);
        void moveForward();
        void turnLeft();
        void turnRight();
        void setDirection(int i);
        int getDirection();
        bool collideWithEntities(double xd, double yd);
        void setTypeAnim(TypeAnim t);

        void goTo(int xt, int yt);
        void moveToDestination();

        virtual void arrivedAtDestination();

        double getSpeed() const;

        void say(std::wstring t);
        bool isSpeaking();
        void addBubbleTime();
        void stopSpeaking();
    protected:
        void drawStillAndMove(sf::RenderWindow* window);

        int direction;
        double speed;
        bool speaking;
        Texture tex;
        TextBox* bubble;
        int frameBubble;

        Point target;
        Point finaltarget;

        int path_step;
        bool goingToDestination;
        std::vector<Point> path;
};
