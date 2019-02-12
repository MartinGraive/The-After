/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <iostream>
#include "Entity.h"
#include "GameCore.h"

Entity::Entity(RenderingArray* a) : array(a)
{
}

Entity::~Entity()
{
}

void Entity::draw(sf::RenderWindow* window)
{
}

void Entity::drawAbove(sf::RenderWindow* window)
{
}

void Entity::process()
{
}

void Entity::setX(double i)
 { x = i; }

void Entity::setY(double i, bool ordering)
{
    double old_y = y;
    y = i;
    if (array!=NULL && ordering){
        array->reorder(y - old_y, renderingOrder, this);
    }
}

void Entity::setXtile(int i)
    {x = i * TILE_SIZE + TILE_SIZE / 2 - baseRect.x - baseRect.w / 2;}

void Entity::setYtile(int i, bool ordering)
    {setY(i * TILE_SIZE + TILE_SIZE / 2 - baseRect.y - baseRect.h / 2, ordering);}

void Entity::setRenderingOrder(int i)
    { renderingOrder = i; }

double Entity::getX() const
    { return x; }

double Entity::getY() const
    { return y; }

double Entity::getXbase() const
    { return x + baseRect.x; }

double Entity::getYbase() const
    { return y + baseRect.y; }

bool Entity::isSolid() const
    { return solid; }

EntityType Entity::getType() const
    { return ENTITY; }

void Entity::move(int xt, int yt)
{
}

Rect Entity::getBaseRect() const
    { return baseRect; }

bool Entity::isInRect(Rect r)
{
    if (this->getXbase() + this->getBaseRect().w >= r.x && this->getXbase() <= r.x + r.w && this->getYbase() + this->getBaseRect().h >= r.y && this->getYbase() <= r.y + r.h) {
        return true;
    }
    else { return false; }
}

void Entity::activate()
{
}
