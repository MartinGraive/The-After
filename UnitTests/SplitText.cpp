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

namespace
{
    TEST(SplitTextTest)
    {
        std::vector<std::string> Result = StringPrimitives::split("bonjour comment allez-vous ?");
        std::vector<std::string> Expected{"bonjour", "comment", "allez-vous", "?"};
        CHECK_ARRAY_EQUAL(Expected, Result, 4);
    }
}
