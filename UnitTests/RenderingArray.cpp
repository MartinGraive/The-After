/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include <UnitTest++.h>
#include <vector>
#include "../Primitives/StringPrimitives.h"
#include "../GameCore.h"
#include "../Vigil.h"

namespace
{
    TEST(RenderingArrayTest)
    {
        GameCore::createInstance();
        RenderingArray* entities = GameCore::getInstance()->getEntities();

        bool sameEntities = false;
        for (int i = 0 ; i < entities->size() ; i++) {
            for (int j = i + 1 ; j < entities->size() ; j++) {
                if (entities->getEntity(i) == entities->getEntity(j)) {
                    sameEntities = true;
                    break;
                }
            }
        }

        CHECK_EQUAL(false, sameEntities);
    }
}


