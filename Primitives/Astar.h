/*THE AFTER
Commenc� le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#ifndef DEF_ASTAR
#define DEF_ASTAR
#include <vector>
#include "../Settings.h"

struct Noeud
{
    int x;
    int y;
    int f;
    int g;
    int h;
    Noeud* parent;
};

std::vector<Point> astar(int x, int y, int x2, int y2);

#endif //DEF_ASTAR

