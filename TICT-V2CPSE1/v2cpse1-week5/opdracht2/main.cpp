#define CATCH_CONFIG_MAIN 

#include "setLib.hpp"
#include "catch.hpp"
#include <iostream>

TEST_CASE("Test same int"){
    setLib <int, 10> list;
    list.add(1);
    list.add(1);
    std::stringstream test;
    test << list;
    REQUIRE(test.str() == "1, 0, 0, 0, 0, 0, 0, 0, 0, 0, ");
}

TEST_CASE("Test out of bounds"){
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
    list.add(11);
    std::stringstream test;
    test << list;
    REQUIRE(test.str() == "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ");
}

TEST_CASE("Test contains function"){
    setLib <int, 10> list;
    list.add(1);
    list.add(8);
    list.add(6);
    list.contains(5);
    list.contains(1);
    REQUIRE(list.contains(5)==false);
    REQUIRE(list.contains(1)==true);
}

TEST_CASE("Test remove function"){
    setLib <int, 10> list;
    list.add(1);
    list.add(1);
    list.add(8);
    list.add(2);
    list.add(3);
    list.add(4); 
    list.remove(8);
    std::stringstream test;
    test << list;
    REQUIRE(test.str() == "1, 2, 3, 4, 0, 0, 0, 0, 0, 0, ");
    list.remove(0);
    std::stringstream test1;
    test1 << list;
    REQUIRE(test1.str() == "1, 2, 3, 4, 0, 0, 0, 0, 0, 0, ");
    list.remove(8);
    std::stringstream test2;
    test2 << list;
    REQUIRE(test2.str() == "1, 2, 3, 4, 0, 0, 0, 0, 0, 0, ");
}

TEST_CASE("Test remove 0 and remove out of bounds"){
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
    list.add(11);
    list.remove(0);
    std::stringstream test;
    test << list;
    REQUIRE(test.str() == "1, 2, 3, 4, 5, 6, 7, 8, 9, 0, ");
    list.add(10);
    list.remove(10);
    std::stringstream test1;
    test1 << list;
    REQUIRE(test1.str() == "1, 2, 3, 4, 5, 6, 7, 8, 9, 0, ");
}

TEST_CASE("Test ostream and remove with int not in list"){
    setLib <int, 10> list;
    list.add(1);
    list.add(1);
    list.add(8);
    list.add(6);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(7);
    list.add(9);
    list.add(10);
    list.add(11);
    list.add(12);
    std::cout<<list<<"\n";    
    list.remove(8);
    std::cout<<list<<"\n";
    std::stringstream test;
    test << list;
    REQUIRE(test.str() == "1, 6, 2, 3, 4, 7, 9, 10, 11, 0, ");
}

// ============================================================
//                      Opdracht 1 Tests ^^
// ============================================================ 

TEST_CASE("Test different type"){
    setLib <float, 10> list;
    list.add(1);
    list.add(1);
    std::stringstream test;
    test << list;
    REQUIRE(test.str() == "1, 0, 0, 0, 0, 0, 0, 0, 0, 0, ");
}

TEST_CASE("Test different type with out of bounds"){
    setLib <float, 10> list;
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
    list.add(11);
    std::stringstream test;
    test << list;
    REQUIRE(test.str() == "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ");
}

TEST_CASE("Test float contains"){
    setLib <float, 10> list;
    list.add(1);
    list.add(8);
    list.add(6);
    list.contains(5);
    list.contains(1);
    REQUIRE(list.contains(5)==false);
    REQUIRE(list.contains(1)==true);
}

TEST_CASE("Test remove with different type, zero and wrong value"){
    setLib <float, 10> list;
    list.add(1);
    list.add(1);
    list.add(8);
    list.add(2);
    list.add(3);
    list.add(4); 
    list.remove(8);
    std::stringstream test;
    test << list;
    REQUIRE(test.str() == "1, 2, 3, 4, 0, 0, 0, 0, 0, 0, ");
    list.remove(0);
    std::stringstream test1;
    test1 << list;
    REQUIRE(test1.str() == "1, 2, 3, 4, 0, 0, 0, 0, 0, 0, ");
    list.remove(8);
    std::stringstream test2;
    test2 << list;
    REQUIRE(test2.str() == "1, 2, 3, 4, 0, 0, 0, 0, 0, 0, ");
}

TEST_CASE("Test float ostream and remove 0 and out of bounds"){
    setLib <float, 10> list;
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
    list.add(11);
    list.remove(0);
    std::stringstream test;
    test << list;
    REQUIRE(test.str() == "1, 2, 3, 4, 5, 6, 7, 8, 9, 0, ");
    list.add(10);
    list.remove(10);
    std::stringstream test1;
    test1 << list;
    REQUIRE(test1.str() == "1, 2, 3, 4, 5, 6, 7, 8, 9, 0, ");
}

TEST_CASE("Test float, out of bounds, remove and print"){
    setLib <float, 10> list;
    list.add(1);
    list.add(1);
    list.add(8);
    list.add(6);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(7);
    list.add(9);
    list.add(10);
    list.add(11);
    list.add(12);
    std::cout<<list<<"\n";    
    list.remove(8);
    std::cout<<list<<"\n";
    std::stringstream test;
    test << list;
    REQUIRE(test.str() == "1, 6, 2, 3, 4, 7, 9, 10, 11, 0, ");
}

TEST_CASE("Test float add with double value"){
    setLib <float, 5> list;
    list.add(1);
    list.add(1);
    std::stringstream test;
    test << list;
    REQUIRE(test.str() == "1, 0, 0, 0, 0, ");
}

TEST_CASE("Test float, add with zero and overflow"){
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
}

TEST_CASE("Test float contains function"){
    setLib <float, 5> list;
    list.add(1);
    list.add(8.8);
    list.add(6);
    list.contains(5);
    list.contains(1);
    REQUIRE(list.contains(5)==false);
    REQUIRE(list.contains(1)==true);
}

TEST_CASE("Test float remove with right, zero and wrong"){
    setLib <float, 5> list;
    list.add(1);
    list.add(1);
    list.add(8);
    list.add(2);
    list.add(3.1);
    list.add(4); 
    list.remove(8);
    std::stringstream test;
    test << list;
    REQUIRE(test.str() == "1, 2, 3.1, 4, 0, ");
    list.remove(0);
    std::stringstream test1;
    test1 << list;
    REQUIRE(test1.str() == "1, 2, 3.1, 4, 0, ");
    list.remove(8);
    std::stringstream test2;
    test2 << list;
    REQUIRE(test2.str() == "1, 2, 3.1, 4, 0, ");
}

TEST_CASE("Test tpye float, remove, zero and out of bounds"){
    setLib <float, 5> list;
    list.add(0);
    list.add(1.7);
    list.add(2);
    list.add(3);
    list.add(4.4);
    list.add(5);
    list.add(6);
    list.add(7);
    list.add(8);
    std::stringstream test;
    test << list;
    REQUIRE(test.str() == "0, 1.7, 2, 3, 4.4, ");
    list.add(10);
    list.remove(10);
    std::stringstream test1;
    test1 << list;
    REQUIRE(test1.str() == "0, 1.7, 2, 3, 4.4, ");
}

// ============================================================
//                      Opdracht 2 Tests ^^
// ============================================================ 