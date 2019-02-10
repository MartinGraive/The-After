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


class Entity;

class RenderingArray
{
    public:
        RenderingArray();
        ~RenderingArray();

        void resizeArray(int i);
        void addEntity(Entity* e);
        void removeEntity(Entity* e);
        void removeEntity(int order);
        void sortEntities();
        Entity* getEntity(int i);
        int size();
        void reorder(double y, int renderingOrder, Entity* e);
    protected:
        std::vector<Entity*> entity;
};

