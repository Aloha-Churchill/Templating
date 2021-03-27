/*
Name: Aloha Churchill
Instructions for Running Program in Test.cpp: g++ test.cpp, ./a.out 
*/
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Counter.hpp"
#include <string>
#include <vector>

// ------------ instantiating different test types (user defined and just regular int) -----------------
//-------------------------------
/*
struct Animal{
    std::string animal_type;
    bool operator==(const Animal &other){
        if(this->animal_type == other.animal_type){
            return true;
        }
        return false;        
    }

    bool operator >(const Animal &other){
        if(this->animal_type > other.animal_type){
            return true;
        }
        return false;
    }

    bool operator <(const Animal &other){
        if(this->animal_type < other.animal_type){
            return true;
        }
        return false;
    }

    std::ostream& operator<<(std::ostream& os){
        os << this->animal_type; 
        return os;        
    }
};


struct Animal cat = {"cat"};
struct Animal dog = {"dog"};
struct Animal bat = {"bat"};
std::vector<struct Animal> animal_vec = {cat, dog, bat};


//Counter<class Animal> c_animal(animal_vec);
//Counter <class Animal> c_animal_empty;

*/
//---- ints
std::vector<int> int_vec = {1,2,3,4,5};

Counter <int> c_ints(int_vec);
Counter <int> c_ints_empty;

// ----------- ------------ Test Cases for Methods ------------------------------------------


TEST_CASE(" Testing default  constructor", "[constructor1]"){
    SECTION("tests for int"){
        REQUIRE(c_ints_empty.getMap().empty() == true);
    }
    
}

TEST_CASE("Testing overloaded constructor", "[constructor2]"){
    SECTION("tests for int"){
        REQUIRE(c_ints.getMap().empty() == false);
        REQUIRE(c_ints.getMap().size() == 5);
        SECTION("all values are initialized to zero"){
            std::vector<int> v = c_ints.Values();
            for(int value: v){
                REQUIRE(value == 0);
            }
        }
    }
}

TEST_CASE("Testing count", "[count]"){
    SECTION("Tests for int"){
        REQUIRE(c_ints.Count() == 0);
        c_ints.Increment(1); //sets count 1 = 1
        c_ints.Increment(2,2); // sets count 2 = 2
        c_ints.Increment(3,2); //sets count 3 = 2
        REQUIRE(c_ints.Count() == 5);
    }
}

TEST_CASE("Testing count for key", "[countkey]"){
    SECTION("Tests for int"){
        REQUIRE(c_ints.Count(1) == 1);
        REQUIRE(c_ints.Count(2) == 2);    
    }
}

TEST_CASE("Testing count for min and max key", "[minmaxcount]"){
    SECTION("Tests for int"){
        REQUIRE(c_ints.Count(1,2) == 1);
        REQUIRE(c_ints.Count(1,3) == 3);
        REQUIRE(c_ints.Count(2,4) == 4);
    }
}

TEST_CASE("Testing remove", "[remove]"){
    SECTION("Tests for int"){
        std::cout << c_ints;
        c_ints.Remove(5);
        REQUIRE(c_ints.getMap().size() == 4);
        std::cout << c_ints;
    }
}

TEST_CASE("Testing increment", "[increment]"){
    SECTION("tests for int"){
        c_ints.Increment(1);
        REQUIRE(c_ints.getMap()[1] == 2);
    }
}

TEST_CASE("Testing increment for + n", "[increment+n]"){
    SECTION("tests for int"){
        c_ints.Increment(1,3);
        REQUIRE(c_ints.getMap()[1] == 5);
    }
}

TEST_CASE("Testing decrement", "[dec]"){
    SECTION("tests for int"){
        c_ints.Decrement(1);
        REQUIRE(c_ints.getMap()[1] == 4);
        c_ints.Decrement(4);
        REQUIRE(c_ints.getMap()[4] == 0);
    }
}

TEST_CASE("Testing decrement -n", "[dec-n]"){
    SECTION("tests for int"){
        c_ints.Decrement(1,5);
        REQUIRE(c_ints.getMap()[1] == 0);
        c_ints.Increment(1,4);
        c_ints.Decrement(1,2);
        REQUIRE(c_ints.getMap()[1] == 2);
    }
}

TEST_CASE("Keys", "[keys]"){
    SECTION("tests for int"){
        std::set<int> correct = {1,2,3,4};
        std::set<int> returned = c_ints.Keys();
        REQUIRE(correct == returned);
    }
}

TEST_CASE("Values", "[vals]"){
    SECTION("tests for int"){
        std::vector<int> correct = {2,2,2,0};
        std::vector<int> returned = c_ints.Values();
        REQUIRE(correct == returned);
    }
}

TEST_CASE("Most common", "[mostcommon]"){
    SECTION("test for int"){
        SECTION("domain error for empty counter"){
            CHECK_THROWS(c_ints_empty.MostCommon());
        }
        int target = 1;
        int returned = c_ints.MostCommon();
        REQUIRE(target == returned);
        c_ints.Increment(2);
        target = 2;
        returned = c_ints.MostCommon();
        REQUIRE(target == returned);
    }
}

TEST_CASE("Most  common n", "[mostcommonn]"){
    SECTION("test for int"){
        SECTION("domain error for empty counter"){
            CHECK_THROWS(c_ints_empty.MostCommon());
        }
        std::vector<int> expected = {1,2};
        std::vector<int> expected2 = {2,1};
        std::vector<int> returned = c_ints.MostCommon(2);
        REQUIRE((expected == returned || expected2 == returned) == true);
    }
}

TEST_CASE("Least common", "[leastcommon]"){
    SECTION("test for int"){
        SECTION("domain error for empty counter"){
            CHECK_THROWS(c_ints_empty.LeastCommon());
        }
        int target = 4;
        int returned = c_ints.LeastCommon();
        REQUIRE(target == returned);
        c_ints.Decrement(1,2);
        target = 1;
        returned = c_ints.LeastCommon();
        REQUIRE(target == returned);
        c_ints.Increment(1,2);
    }
}

TEST_CASE("Least  common n ", "[leastcommonn]"){
    SECTION("test for int"){
        SECTION("domain error for empty counter"){
            CHECK_THROWS(c_ints_empty.LeastCommon(2));
        }
        
        //c_ints_tom = 1:1,2:3,3:2,4:0
        std::vector<std::string> v_new = {"1","2","3","4"};
        Counter <std::string> d(v_new);
        d.Increment("1",1);
        d.Increment("2",2);
        d.Increment("3",4);
        d.Increment("4",5);
        d.Increment("5a", 2);
        d.Increment("5a", 4);
        std::cout << "vector";
        std::cout << d;
        std::vector<std::string> returned = d.LeastCommon(2);
        for(std::string v: returned){
            std::cout << v << ",";
        }

        /*
        std::cout << c_ints;
        std::vector<int> expected = {1,4};
        std::vector<int> expected2 = {4,1};
        std::vector<int> returned = c_ints.LeastCommon(2);
        REQUIRE((expected == returned || expected2 == returned) == true);
        */
    }
}

TEST_CASE("Normalized", "[Normalized]"){
    SECTION("test for int "){
        c_ints.Increment(4); //total is 8
        std::map<int, double> expected;
        expected[1] = 0.25;
        expected[2] = 0.375;
        expected[3] = 0.25;
        expected[4] = 0.125;

        std::map<int, double> returned = c_ints.Normalized();
        for(int i=1; i<5; i++){
            REQUIRE(returned[i] == expected[i]);
        }        
    }
}


//not unit testing for overloading operator