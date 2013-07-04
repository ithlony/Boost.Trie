#define BOOST_TEST_MODULE trie_test
#include <boost/test/unit_test.hpp>
#include "trie.hpp"
#include "trie.hpp"
#include <string>

BOOST_AUTO_TEST_SUITE(trie_test)

BOOST_AUTO_TEST_CASE(operator_test)
{
	boost::tries::trie_map<char, int> t;
	/*
	std::string s = "aaa", s2 = "bbb";
	t[s] = 1;
	BOOST_CHECK(t[s] == 1);
	t[s] = 2;
	BOOST_CHECK(t[s] == 1);
	t[s2] = t[s];
	BOOST_CHECK(t[s] == t[s2]);
	*/

}

BOOST_AUTO_TEST_CASE(insert_test)
{
	boost::tries::trie_map<char, int> t;

}

BOOST_AUTO_TEST_SUITE_END()
