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
    TEST(SeesPlayerClear)
    {
        GameCore::createInstance();
        GameCore::getInstance()->getMPlayer()->setX(300);
        GameCore::getInstance()->getMPlayer()->setY(180, false);

        Vigil* v = new Vigil(TextureHandler::getInstance()->getVigils(0), GameCore::getInstance()->getEntities());
        v->setX(180);
        v->setY(180, false);
        GameCore::getInstance()->addCharacter(v);
        v->setDirection(DROITE);
        bool Result = v->seesPlayer();

        CHECK_EQUAL(true, Result);

        delete GameCore::getInstance();
    }
    TEST(SeesPlayerObstacle)
    {
        GameCore::createInstance();
        GameCore::getInstance()->getMPlayer()->setX(500);
        GameCore::getInstance()->getMPlayer()->setY(180, false);

        Vigil* v = new Vigil(TextureHandler::getInstance()->getVigils(0), GameCore::getInstance()->getEntities());
        v->setX(180);
        v->setY(180, false);
        GameCore::getInstance()->addCharacter(v);

        GameCore::getInstance()->getMap()->setSolid(30, 12, true);
        GameCore::getInstance()->getMap()->setSolid(30, 13, true);
        GameCore::getInstance()->getMap()->setSolid(30, 14, true);

        v->setDirection(DROITE);
        bool Result = v->seesPlayer();

        CHECK_EQUAL(false, Result);

        delete GameCore::getInstance();
    }
}

