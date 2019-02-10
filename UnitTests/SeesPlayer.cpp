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
    /*TEST(SeesPlayerClear)
    {
        GameCore::createInstance();
        GameCore::getInstance()->getMPlayer()->setX(500);

        Vigil* v = dynamic_cast<Vigil*>(GameCore::getInstance()->getCharacters(0));
        v->setDirection(DROITE);
        bool Result = v->seesPlayer();

        delete GameCore::getInstance();

        CHECK_EQUAL(true, Result);
    }
    TEST(SeesPlayerObstacle)
    {
        GameCore::createInstance();
        GameCore::getInstance()->getMPlayer()->setX(500);

        GameCore::getInstance()->getMap()->setSolid(30, 12, true);
        GameCore::getInstance()->getMap()->setSolid(30, 13, true);
        GameCore::getInstance()->getMap()->setSolid(30, 14, true);

        Vigil* v = dynamic_cast<Vigil*>(GameCore::getInstance()->getCharacters(0));
        v->setDirection(DROITE);
        bool Result = v->seesPlayer();

        CHECK_EQUAL(false, Result);
    }*/
}

