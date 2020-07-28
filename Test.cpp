/*
 * Test.cpp
 *
 *  Created on: 15 June 2020
 *      Author: oriel malihi
 */
#include "doctest.h"
#include <string>
#include <vector>
#include "range.hpp"
#include "accumulate.hpp"
#include "filterfalse.hpp"
#include "compress.hpp"

#define EPSILON 0.00001

using namespace itertools;
using namespace std;

range my_range = range(5, 10);
vector<int> vecInt = {2, 4, 6, 8};
vector<string> vecString = {"Hello", "Bye", "Shalom"};
vector<float> vecFloat = {-1, 0.3, 5.2, -4};

template <typename T>
struct functor
{
    T operator()(T a, T b)
    {
        return (a + b) * 2;
    }
};

template <typename T>
struct bool_functor
{
    bool operator()(T val)
    {
        return (val+5)%10==0;
    }
};

TEST_CASE("Range class")
{

    int expected = 5;
    for (auto i : my_range)
    {
        CHECK(i == expected);
        expected++;
    }
    CHECK(expected == 10);
}

TEST_CASE("accumulate class")
{
    auto my_container = accumulate(vecInt);
    int ans[] = {2, 6, 12, 20};
    int index = 0;
    for (auto i : my_container)
    {
        CHECK(i == ans[index]);
        index++;
    }

    auto my_container2 = accumulate(vecFloat);
    float ans2[] = {-1, -0.7, 4.5, 0.5};
    index = 0;
    for (auto i : my_container2)
    {
        if (i < ans2[index] + EPSILON && i > ans2[index] - EPSILON)
        {
            CHECK(true);
        }
        else
        {
            CHECK(false);
        }
        index++;
    }

    auto container3 = accumulate(vector({string("my "), string("name "), string("is "), string("oriel")}));
    string ans3[] = {"my ", "my name ", "my name is ", "my name is oriel"};
    index = 0;
    for (auto i : container3){
        CHECK(ans3[index].compare(i)==0);
        index++;
    }
}

TEST_CASE("accumulate class with Functor")
{
    auto my_container = accumulate(vecInt, functor<int>());
    int ans[] = {2, 12, 36, 88};
    int index = 0;
    for (auto i : my_container)
    {
        CHECK(i == ans[index]);
        index++;
    }

    auto my_container2 = accumulate(vecFloat, functor<float>());
    float ans2[] = {-1, -1.4, 7.6, 7.2};
    index = 0;
    for (auto i : my_container2)
    {
        if (i < ans2[index] + EPSILON && i > ans2[index] - EPSILON)
        {
            CHECK(true);
        }
        else
        {
            CHECK(false);
        }
        index++;
    }
}

TEST_CASE("filterfale class")
{
    auto  c1 = filterfalse(bool_functor<int>(), vector({1,2,5,25,15,21,28,43,52}));
    int ans[] = {1,2,21,28,43,52};
    int index = 0;
    for(auto i : c1){
        CHECK(i==ans[index]);
        index++;
    }

    auto lam = [](int val){return (val+5)%10==0;};
    auto  c2 = filterfalse(lam, vector({1,2,5,25,15,21,28,43,52}));
    int ans2[] = {1,2,21,28,43,52};
    index = 0;
    for(auto i : c2){
        CHECK(i==ans2[index]);
        index++;
    }

    auto lam2 = [](int val){return val<7;};
    auto c3 = filterfalse(lam2, my_range);
    int ans3[] = {7,8,9};
    index = 0;
    for(auto i : c3){
        CHECK(i==ans3[index]);
        index++;
    }


}

TEST_CASE("compress class"){
    string name = "oriel";
    auto v1 = vector({true,true,true,false,false});
    auto c1 = compress(name, v1);
    char ans[]={'o', 'r', 'i'};
    int index = 0;
    for(auto i : c1){
        CHECK(i==ans[index]);
        index++;
    }
    
}

TEST_CASE("some more.."){
    range r = range(0,60);
    int expected = 0;
    for(int i : r){
        CHECK(i==expected);
        expected++;
    }
}

