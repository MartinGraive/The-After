/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <algorithm>
#include <functional>
#include <iostream>
#include "Entity.h"
#include "RenderingArray.h"

bool myfunction (int i,int j) { return (i<j); }

bool compare(Entity const* a, Entity const* b)
{
    return a->getY() < b->getY();
}

RenderingArray::RenderingArray()
{
}

RenderingArray::~RenderingArray()
{
    for (int i = 0 ; i<size() ; i++) {
        delete entity[i];
    }
}

void RenderingArray::resizeArray(int i)
    { entity.resize(i); }

void RenderingArray::addEntity(Entity* e)
{
    int i = 0;
    while (i < (int)(entity.size()) && e->getY() > entity[i]->getY()) {
        i++;
    }
    entity.push_back(NULL);
    for (int j = (int)(entity.size()) - 1 ; j > i ; j--) { entity[j] = entity[j-1]; entity[j]->setRenderingOrder(j); }
    entity[i] = e;
    e->setRenderingOrder(i);
}

void RenderingArray::sortEntities()
{
    std::sort(entity.begin(),entity.end(), compare);
    for (int i = 0 ; i < size() ; i++) {
        entity[i] -> setRenderingOrder(i);
    }
}

Entity* RenderingArray::getEntity(int i)
    { return entity[i]; }

int RenderingArray::size()
    { return (int)(entity.size()); }

void RenderingArray::reorder(double y, int renderingOrder, Entity* e)
{
    if (entity.size() > 0) {
        int j = renderingOrder;
        while ((j > 0 && j < size() && y < 0 && e->getYbase() < entity[j-1]->getYbase()) || (j >= 0 && j < size() - 1 && y > 0 && e->getYbase() > entity[j+1]->getYbase())) {
            if (y < 0) j--;
            else j++;
        }
        //std::cout<<"renderingOrder="<<renderingOrder<<" J ="<<j<<" size="<<size()<<" y="<<y<<"\n";
        if (y < 0) {
            for (int k = renderingOrder ; k>j ; k--) { entity[k] = entity[k-1]; entity[k]->setRenderingOrder(k); }
        }
        else {
            for (int k = renderingOrder ; k<j ; k++) { entity[k] = entity[k+1]; entity[k]->setRenderingOrder(k); }
        }
        // 0 < 1 -> entity[0]= entity[1]....... et entity[1] = e
        entity[j] = e;
        e->setRenderingOrder(j);
    }
}
