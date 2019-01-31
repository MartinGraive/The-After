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
