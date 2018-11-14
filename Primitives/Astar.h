/*Random Game
Started on 27/01/2018

Grade (programming / Concept)*/

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

