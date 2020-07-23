#include "doctest.h"
#include <iostream>
#include <vector>
#include <limits>

#include "range.hpp"
#include "accumulate.hpp"
#include "filterfalse.hpp"
#include "compress.hpp"


using namespace itertools;
using namespace std;

TEST_CASE("range") {
    int j = 0;
    for (int i: range(0,50)){ 
		CHECK(i==j++);     
    }
}

TEST_CASE("accumulate of range") {
    int k = 0;
	for (int i: accumulate(range(0,50))) {
        CHECK(i==k*(k+1)/2);
        k++;
    }

}
TEST_CASE("accumulate of string"){
    vector<string> v = {"a", "v", "i", "t", "a", "l"};
    string words[] = {"a", "av", "avi", "avit", "avita", "avital"};
    int j = 0;
    for(auto i : accumulate(v)){
        CHECK(i == words[j++]);
    }
}

TEST_CASE("filterfalse") {
    for (auto i: filterfalse([](int x){return x%2==1;}, range(1,50)))
        CHECK(i%2==0);
}

TEST_CASE("compress") {
    vector<bool> bool_vector = {true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true};
    for (auto i: compress(range(0,25), bool_vector)) {
        CHECK(i%2 == 0);
    }
} 
