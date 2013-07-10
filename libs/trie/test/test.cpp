#define BOOST_TEST_MODULE trie_test
#include <boost/test/unit_test.hpp>
// test include guard
#include "boost/trie/trie.hpp"
#include "boost/trie/trie.hpp"
#include <string>
#include <iostream>

BOOST_AUTO_TEST_SUITE(trie_test)

BOOST_AUTO_TEST_CASE(operator_test)
{
	boost::tries::trie_map<char, int> t;
	std::string s = "aaa", s2 = "bbb";
	t[s] = 1;
	BOOST_CHECK(t[s] == 1);
	t[s] = 2;
	BOOST_CHECK(t[s] == 2);
	t[s2] = t[s];
	BOOST_CHECK(t[s] == t[s2]);

}

BOOST_AUTO_TEST_CASE(insert_and_find_test)
{
	boost::tries::trie_map<char, int> t;
	std::string s = "aaa", s1 = "aaaa", s2 = "aab", s3 = "bbb";
	t[s] = 1;
	BOOST_CHECK(*t.find(s) == 1);
	BOOST_CHECK(t.find(s) != t.end());
	BOOST_CHECK(t.find(s2) == t.end());
	BOOST_CHECK(t.find(s2) == t.end());
	t[s] = 2;
	BOOST_CHECK(*t.find(s) == 2);
	t[s2] = t[s];
	BOOST_CHECK(t.find(s2) != t.end());
	BOOST_CHECK(t.find(s1) == t.find(s3));
	BOOST_CHECK(t.find(s) != t.find(s2));
	BOOST_CHECK((t.insert(s1, 3).second == true));
	BOOST_CHECK((t.insert(s3, 10).second == true));
	BOOST_CHECK((t.insert(s2, 10)).second == false);
	BOOST_CHECK((t.insert(s, 10)).second == false);
}

BOOST_AUTO_TEST_CASE(iterator_operator_plus)
{
	boost::tries::trie_map<char, int> t;
	std::string s = "aaa", s1 = "aaaa", s2 = "aab", s3 = "bbb";
	BOOST_CHECK(t.empty() == true);
	BOOST_CHECK(t.size() == 0);
	BOOST_CHECK(t.begin() == t.end());
	t[s] = 1;
	t[s1] = 2;
	t[s2] = 3;
	BOOST_CHECK(t.begin() != t.end());
	std::cout << "kaka" << std::endl;
	boost::tries::trie_map<char, int>::iterator ti;
	ti = t.begin();
	std::cout << "haha" << std::endl;
	BOOST_CHECK(*ti == 1);
	std::cout << "haha" << std::endl;
	++ti;
	BOOST_CHECK(*ti == 2);
	std::cout << "haha" << std::endl;
	BOOST_CHECK(t[s2] == 3);
	std::cout << "wawa" << std::endl;
	++ti;
	BOOST_CHECK(*ti == 3);
	std::cout << "haha" << std::endl;
	++ti;
	std::cout << "haha" << std::endl;
	BOOST_CHECK(ti == t.end());
}

BOOST_AUTO_TEST_SUITE_END()
