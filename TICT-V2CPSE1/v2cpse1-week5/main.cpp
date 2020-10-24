#define CATCH_CONFIG_MAIN 

#include "setLib.hpp"
#include "catch.hpp"
#include <array>
#include <iostream>

TEST_CASE("TEST: Add, Double, Max"){
    setLib <int, 10> list;
    list.add(1);
    list.add(1);
    std::stringstream test;
    test << list;
    REQUIRE(test.str() == "1, 0, 0, 0, 0, 0, 0, 0, 0, 0, ");
    std::stringstream test1;
    test1 << list.max();
    REQUIRE(test1.str() == "1");
}

TEST_CASE("TEST: Add, Zero, out of bounds, Max"){
    setLib <int, 10> list;
    list.add(0);
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5);
    list.add(6);
    list.add(7);
    list.add(8);
    list.add(9);
    list.add(10);
    std::stringstream test;
    test << list;
    REQUIRE(test.str() == "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ");
    std::stringstream test1;
    test1 << list.max();
    REQUIRE(test1.str() == "9");
}


TEST_CASE("TEST: Differnt type, Add, Double, Max"){
    setLib <float, 10> list;
    list.add(1);
    list.add(1);
    std::stringstream test;
    test << list;
    REQUIRE(test.str() == "1, 0, 0, 0, 0, 0, 0, 0, 0, 0, ");
    std::stringstream test1;
    test1 << list.max();
    REQUIRE(test1.str() == "1");
}

TEST_CASE("TEST: Differnt type, Add, Out of Bounds, Max"){
    setLib <float, 10> list;
    list.add(0);
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5);
    list.add(6);
    list.add(7);
    list.add(8.6);
    list.add(9);
    list.add(10);
    std::stringstream test;
    test << list;
    REQUIRE(test.str() == "0, 1, 2, 3, 4, 5, 6, 7, 8.6, 9, ");
    std::stringstream test1;
    test1 << list.max();
    REQUIRE(test1.str() == "9");
}

TEST_CASE("TEST: Differnt type and length, Add, Double, Max"){
    setLib <float, 5> list;
    list.add(1);
    list.add(1);
    std::stringstream test;
    test << list;
    REQUIRE(test.str() == "1, 0, 0, 0, 0, ");
    std::stringstream test1;
    test1 << list.max();
    REQUIRE(test1.str() == "1");
}

TEST_CASE("TEST: Differnt type and length, Add, Out of Bounds, Max"){
    setLib <float, 5> list;
    list.add(0);
    list.add(1);
    list.add(2.2);
    list.add(3.0);
    list.add(4.0);
    list.add(5.0);
    list.add(8);
    std::stringstream test;
    test << list;
    REQUIRE(test.str() == "0, 1, 2.2, 3, 4, ");
    std::stringstream test1;
    test1 << list.max();
    REQUIRE(test1.str() == "4");
}

TEST_CASE("TEST: char, Add, Double, Max"){
    setLib <std::array<char, 3>, 3> list;
    // list.add('A');
    // list.add('A');
    // list.add('X');
    // list.add('Z');
    std::stringstream test;
    test << list;
    REQUIRE(test.str() == "A, X, Z, ");
    std::stringstream test1;
    test1 << list.max();
    REQUIRE(test1.str() == "Z");
}
