#include <iostream>
#include "gtest/gtest.h"
#include "HashMap.hpp"
#include <string>
#include <sstream>

int main3(int argc , char *argv[])
{
    testing::InitGoogleTest(&argc , argv);
    return RUN_ALL_TESTS();
}



/**
 * HashMap related tests.
 */
TEST(HashMapTest , DefaultConstructor)
{
    HashMap<double,double> hashMap;
    EXPECT_EQ(hashMap.size() , 0);
    EXPECT_EQ(hashMap.capacity() , 16);
    EXPECT_EQ(hashMap.getLoadFactor() , 0);
	EXPECT_EQ(hashMap.empty(), true);
	EXPECT_EQ(hashMap.containsKey(double()), false);
}

TEST(HashMapTest, minMaxFactorConstructor)
{
    HashMap<std::string, std::string> hashMap(0, 1);

    EXPECT_EQ(hashMap.size() , 0);
    EXPECT_EQ(hashMap.capacity() , 16);
    EXPECT_EQ(hashMap.getLoadFactor() , 0);
    EXPECT_EQ(hashMap.empty(), true);
    //todo Death Tests
}

TEST(HashMapTest, copyCtor)
{
	HashMap<double, double> hashMap;
    hashMap.insert(1.5,2);
	HashMap<double, double> hashMap1(hashMap);
    EXPECT_EQ(hashMap.size() , 1);
	EXPECT_EQ(hashMap.size() , hashMap1.size());

	EXPECT_EQ(hashMap.capacity(), 16);
	EXPECT_EQ(hashMap.capacity() , hashMap1.capacity());

	EXPECT_EQ(hashMap.getLoadFactor() , hashMap1.getLoadFactor());
	EXPECT_EQ(hashMap.empty(), hashMap1.empty());
    EXPECT_EQ(hashMap.containsKey(1.5), true);
    EXPECT_EQ(hashMap1.containsKey(1.5), true);

    hashMap.erase(1.5);              //check deep copy
	EXPECT_EQ(hashMap.containsKey(1.5), false);
	EXPECT_NE(hashMap.containsKey(1.5), hashMap1.containsKey(1.5));
    EXPECT_NE(hashMap.size() , hashMap1.size());

}

TEST(HashMapTest, vectorCtor)
{

    //small
    std::vector<int> keys{96, 97, 98, 99};
    std::vector<std::string> values{"aa", "bb", "c", "d"};
    HashMap<int, std::string> h(keys, values);
    EXPECT_EQ(h.capacity(), 16);
    EXPECT_EQ(h.size(), 4);
    for (int i = 0; i< 4;i++)
    {
        EXPECT_EQ(h.containsKey(keys[i]), true);
        EXPECT_EQ(h.at(keys[i]).compare(values[i]), false);
    }

    for (int i = 0; i < 96; i++)
    {
        keys.push_back(i);
        char c =(char) i;
        values.emplace_back(&c);
    }

    //big
    HashMap<int, std::string> s(keys, values);
    EXPECT_EQ(s.capacity(), 256);
    EXPECT_EQ(s.size(), 100);

    for (int i = 0; i< 100;i++)
    {
        s.containsKey(keys[i]);
        EXPECT_EQ(s.containsKey(keys[i]), true);
        EXPECT_EQ(s.at(keys[i]).compare(values[i]), false);
    }

    //same key
    std::vector<int> keys2(100,100);
    HashMap<int, int> t(keys2, keys);
    EXPECT_EQ(t.capacity(), 16);
    EXPECT_EQ(t.size(), 1);
    EXPECT_EQ(t.at(100), 95);

    //empty
    std::vector<int> k;
    std::vector<double> v;
    HashMap<int,double> r(k,v);
    EXPECT_EQ(r.capacity(), 16);
    EXPECT_EQ(r.size(), 0);
}

TEST(HashMapTest, insertAndErase)
{
	HashMap<double,std::string> h;
    EXPECT_EQ(h.capacity(), 16);
    EXPECT_EQ(h.size(), 0);

    EXPECT_EQ(h.insert(0, "a"), true);
    EXPECT_EQ(h.capacity(), 16);
    EXPECT_EQ(h.size(), 1);

    // insert
    EXPECT_EQ(h.insert(0, "b"), false);
    EXPECT_EQ(h.capacity(), 16);
    EXPECT_EQ(h.size(), 1);

    for (int i = 1; i <= 11; i++)
    {
        EXPECT_EQ(h.insert(i, "b"),true);
        EXPECT_EQ(h.capacity(), 16);
        EXPECT_EQ(h.size(), i+1);
        EXPECT_EQ(h.getLoadFactor(), (double) h.size()/h.capacity());
    }

    EXPECT_EQ(h.insert(12, "c"),true);
    EXPECT_EQ(h.capacity(), 32);
    EXPECT_EQ(h.size(), 13);


    // erase
    EXPECT_EQ(h.erase(15),false);
    EXPECT_EQ(h.capacity(), 32);
    EXPECT_EQ(h.size(), 13);

    for (int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(h.erase(i),true);
        EXPECT_EQ(h.capacity(), 32);
        EXPECT_EQ(h.size(), 12 - i);
    }
    //8 items left
    for (int i = 5; i < 9; ++i)
    {
        EXPECT_EQ(h.erase(i),true);
        EXPECT_EQ(h.capacity(), 16);
        EXPECT_EQ(h.size(), 12 - i);
    }
    //4 items left
    for (int i = 9; i < 11; ++i)
    {
        EXPECT_EQ(h.erase(i),true);
        EXPECT_EQ(h.capacity(), 8);
        EXPECT_EQ(h.size(), 12 - i);
    }
    EXPECT_EQ(h.erase(11),true);
    EXPECT_EQ(h.capacity(), 4);
    EXPECT_EQ(h.size(), 1);

    EXPECT_EQ(h.erase(12),true);
    EXPECT_EQ(h.capacity(), 2);
    EXPECT_EQ(h.size(), 0);

}

//TEST(HashMapTest, iterator)
//{
//    std::vector<int> keys = {5, 233, 6238, 2100};
//    std::vector<std::string> values = {"a", "b", "c", "d"};
//    HashMap<int, std::string> h(keys, values);
//    for (auto k : h)
//    {
//
//    }
//}


TEST(HashMapTest, atAndSubscript)
{
    std::vector<int> keys = {5, 233, 6238, 2100};
    std::vector<std::string> values = {"a", "b", "c", "d"};
    HashMap<int, std::string> h(keys, values);
    for (int i = 0; i< 4; i++)
    {
        int key = keys[i];
        std::string value = values[i];
        EXPECT_EQ(h.at(key),value);
        EXPECT_EQ(h[key], value);
        h.at(key) = "foo";
        EXPECT_EQ(h.at(key).compare("foo"), false);
        h[key] = "bar";
        EXPECT_EQ(h[key].compare("bar"), false);
    }
    h[4444] = "a";
    EXPECT_EQ(h[4444].compare("a"), false);
    EXPECT_EQ(h.at(4444).compare("a"), false);
    h.erase(4444);
    ASSERT_ANY_THROW(h.at(4444));
}

TEST(HashMapTest, compare)
{
    std::vector<int> keys = {2100, 5, 233, 6238};
    std::vector<std::string> values = {"a", "b", "c", "d"};
    HashMap<int, std::string> h(keys, values);
    HashMap<int, std::string> s(keys, values);
    ASSERT_EQ(h == s, true);
    ASSERT_EQ(h != s, false);
    s[5] = "e";
    ASSERT_EQ(h == s, false);
    ASSERT_EQ(h != s, true);
    s[5] = "b";
	ASSERT_EQ(h == s, true);
	ASSERT_EQ(h != s, false);
	s[6] = "t";
	ASSERT_EQ(h == s, false);
	ASSERT_EQ(h != s, true);
	s[21] = "k";
	h[21] = "k";
	h[6] = "t";
	ASSERT_EQ(h == s, true);
	ASSERT_EQ(h != s, false);

	s.clear();
	h.clear();
	ASSERT_EQ(h == s, true);
	ASSERT_EQ(h != s, false);

	//Non equal capacity test
	for (int i = 0; i < 4; ++i)
	{
        char c =(char) i;
	    h[i] = c;
	}
	for (int i = 0; i < 13; ++i)
    {
        char c =(char) i;
	    s[i] = c;
    }
    s.clear();
    for (int i = 0; i < 4; ++i)
    {
        char c =(char) i;
        s[i] = c;
    }
    ASSERT_EQ(h == s, false);
    ASSERT_EQ(h != s, true);
}