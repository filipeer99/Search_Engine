#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <string>
#include "doctest.h"

using std::string;

void changeBrand(string &car1, string &car2)
{
    string aux = car1;
    car1 = car2;
    car2 = aux;
}

TEST_SUITE("Troca marca") {
    TEST_CASE("changeBrand()") {
        string c1 = "bmw";
        string c2 = "mercedes";
        changeBrand(c1,c2);
        REQUIRE(c1 == "mercedes");
        CHECK(c2 == "bmw");
    }
}




