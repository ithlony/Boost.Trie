#define BOOST_TEST_MODULE trie_test
#include <boost/test/unit_test.hpp>
#include "boost/trie/trie.hpp"
#include "boost/trie/trie.hpp"
#include <string>
#include <iostream>

BOOST_AUTO_TEST_SUITE(trie_multiset_test)

typedef boost::tries::trie_multiset<char> tmsi;
typedef typename tmsi::iterator ti;

BOOST_AUTO_TEST_CASE(insert_find_test)
{
	tmsi a;
	std::string s = "aaa", s2 = "bbb";

	BOOST_CHECK(a.size() == 0);
	BOOST_CHECK(a.find(s) == a.end());
	BOOST_CHECK(a.find(s2) == a.end());
	BOOST_CHECK(a.count(s) == 0);
	BOOST_CHECK(a.count(s2) == 0);

	a.insert(s);
	BOOST_CHECK(a.find(s) != a.end());
	BOOST_CHECK(a.size() == 1);
	BOOST_CHECK(a.count(s) == 1);
	a.insert(s);
	BOOST_CHECK(a.size() == 2);
	BOOST_CHECK(a.count(s) == 2);
	a.insert(s);
	BOOST_CHECK(a.size() == 3);
	BOOST_CHECK(a.count(s) == 3);

	a.insert(s2);
	BOOST_CHECK(a.size() == 4);
	BOOST_CHECK(a.count(s2) == 1);
	BOOST_CHECK(a.find(s2) != a.end());
	a.insert(s2);
	BOOST_CHECK(a.size() == 5);
	BOOST_CHECK(a.count(s2) == 2);
	a.insert(s2);
	BOOST_CHECK(a.size() == 6);
	BOOST_CHECK(a.count(s2) == 3);
	a.insert(s2);
	BOOST_CHECK(a.size() == 7);
	BOOST_CHECK(a.count(s2) == 4);
}

BOOST_AUTO_TEST_CASE(erase_test)
{
	tmsi a;
	ti i;
	std::string s = "aaa", s2 = "bbb";

	BOOST_CHECK(a.size() == 0);
	BOOST_CHECK(a.find(s) == a.end());
	BOOST_CHECK(a.find(s2) == a.end());
	BOOST_CHECK(a.count(s) == 0);
	BOOST_CHECK(a.count(s2) == 0);

	i = a.insert(s);
	a.erase(i);
	BOOST_CHECK(a.size() == 0);
	BOOST_CHECK(a.find(s) == a.end());
	BOOST_CHECK(a.count(s) == 0);

	i = a.insert(s);
	i = a.insert(s);
	a.erase(i);
	BOOST_CHECK_MESSAGE(a.size() == 1, a.size());
	BOOST_CHECK(a.find(s) != a.end());
	BOOST_CHECK_MESSAGE(a.count(s) == 1, a.count(s));
	i = a.insert(s);
	BOOST_CHECK_MESSAGE(a.size() == 2, a.size());
	BOOST_CHECK(a.find(s) != a.end());
	BOOST_CHECK_MESSAGE(a.count(s) == 2, a.count(s));

	i = a.insert(s);
	i = a.insert(s);
	a.erase(s);
	BOOST_CHECK_MESSAGE(a.size() == 0, a.size());
	BOOST_CHECK(a.find(s) == a.end());
	BOOST_CHECK_MESSAGE(a.count(s) == 0, a.count(s));

	BOOST_CHECK_MESSAGE(a.count_node() == 0, a.count_node());
	i = a.insert(s2);
	BOOST_CHECK_MESSAGE(a.count_node() == 3, a.count_node());
	i = a.insert(s);
	BOOST_CHECK_MESSAGE(a.count_node() == 6, a.count_node());

	BOOST_CHECK_MESSAGE(a.size() == 2, a.size());
	BOOST_CHECK(a.find(s) != a.end());
	BOOST_CHECK_MESSAGE(a.count(s) == 1, a.count(s));

	i = a.insert(s);
	BOOST_CHECK_MESSAGE(a.size() == 3, a.size());
	BOOST_CHECK_MESSAGE(a.count(s) == 2, a.count(s));

	i = a.insert(s2);
	BOOST_CHECK_MESSAGE(a.size() == 4, a.size());
	BOOST_CHECK_MESSAGE(a.count(s2) == 2, a.count(s2));

	i = a.erase(i);
	BOOST_CHECK_MESSAGE(a.size() == 3, a.size());
	BOOST_CHECK_MESSAGE(a.count(s2) == 1, a.count(s2));

	a.erase(i);
	BOOST_CHECK_MESSAGE(a.size() == 2, a.size());
	BOOST_CHECK_MESSAGE(a.count(s2) == 0, a.count(s2));
	
	a.insert(s2);
	a.insert(s);
	i = a.begin();
	int size = 3;
	while (i != a.end())
	{
		i = a.erase(i);
		BOOST_CHECK_MESSAGE(a.size() == size, a.size());
		--size;
	}
}

BOOST_AUTO_TEST_CASE(equal_range_test)
{
	tmsi a;
	ti i;
	std::string s = "aaa", s2 = "bbb";


	i = a.insert(s);
	a.erase(i);
	std::cout << "dd" << std::endl;
	std::pair< ti, ti > pii = a.equal_range(s);
	int count = 0;
	std::cout << "dd" << std::endl;
	ti first = pii.first, last = pii.second;
	for (; first != last; ++first)
	{
		++count;
	}
	std::cout << "dd" << std::endl;
	BOOST_CHECK_MESSAGE(count == 0, count);
	i = a.insert(s);
	pii = a.equal_range(s);
	count = 0;
	first = pii.first, last = pii.second;
	for (; first != last; ++first)
	{
		++count;
	}
	BOOST_CHECK_MESSAGE(a.count(s) == 1, a.count(s));
	BOOST_CHECK_MESSAGE(count == 1, count);
	i = a.insert(s);
	pii = a.equal_range(s);
	count = 0;
	first = pii.first, last = pii.second;
	for (; first != last; ++first)
	{
		++count;
	}
	BOOST_CHECK_MESSAGE(a.count(s) == 2, a.count(s));
	BOOST_CHECK_MESSAGE(count == 2, count);
}

/*
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

BOOST_AUTO_TEST_CASE(copy_test)
{
	boost::tries::trie_map<char, int> t, t2;
	std::string s = "aaa", s1 = "aaaa", s2 = "aab", s3 = "bbb";
	t[s] = 1; t[s1] = 2; t[s2] = 3; t[s3] = 4;
	t2 = t;
	BOOST_CHECK(t2.size() == 4);
	BOOST_CHECK(t2.count_node() == 8);
	BOOST_CHECK(t2[s] == 1);
	BOOST_CHECK(t2[s1] == 2);
	BOOST_CHECK(t2[s2] == 3);
	BOOST_CHECK(t2[s3] == 4);
	boost::tries::trie_map<char, int> t3(t2);
	BOOST_CHECK(t3.size() == 4);
	BOOST_CHECK(t3.count_node() == 8);
	BOOST_CHECK(*t3.find(s) == 1);
	BOOST_CHECK(*t3.find(s1) == 2);
	BOOST_CHECK(*t3.find(s2) == 3);
	BOOST_CHECK(*t3.find(s3) == 4);
	t3[std::string("a")] = 10;
	BOOST_CHECK(t3.size() == 5);
	BOOST_CHECK(t3.count_node() == 8);
	BOOST_CHECK(*t3.begin() == 10);
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
	boost::tries::trie_map<char, int>::iterator ti;
	ti = t.begin();
	BOOST_CHECK(*ti == 1);
	++ti;
	BOOST_CHECK(*ti == 2);
	BOOST_CHECK(t[s2] == 3);
	++ti;
	BOOST_CHECK(*ti == 3);
	++ti;
	BOOST_CHECK(ti == t.end());
	// test ++end()
	++ti;
	BOOST_CHECK(ti == t.end());
}

BOOST_AUTO_TEST_CASE(iterator_operator_minus)
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
	boost::tries::trie_map<char, int>::iterator ti;
	boost::tries::trie_map<char, int>::const_iterator cti(t.end());
	ti = t.begin();
	BOOST_CHECK(*ti == 1);
	*ti = 10;
	BOOST_CHECK(*ti == 10);
	cti = t.begin();
	BOOST_CHECK(*cti == 10);
	--ti;
	BOOST_CHECK(ti == t.end());
	BOOST_CHECK(t[s2] == 3);
	--ti;
	BOOST_CHECK(*ti == 3);
	t[s3] = 4;
	++ti;
	BOOST_CHECK(*ti == 4);
	++ti;
	BOOST_CHECK(ti == t.end());
	++ti;
	BOOST_CHECK(ti == t.end());
	--ti;
	BOOST_CHECK(*ti == 4);
	BOOST_CHECK(t.count_node() == 8);
	BOOST_CHECK(t.size() == 4);
}

BOOST_AUTO_TEST_CASE(clear)
{
	boost::tries::trie_map<char, int> t;
	std::string s = "aaa", s1 = "aaaa", s2 = "aab", s3 = "bbb";
	t[s] = t[s1] = t[s2] = t[s3] = 10;
	int node_cnt = t.count_node();
	BOOST_CHECK(t.size() == 4);
	BOOST_CHECK(t.count_node() == node_cnt);
	t.clear();
	BOOST_CHECK(t.size() == 0);
	BOOST_CHECK(t.count_node() == 0);
	BOOST_CHECK(t[s] == 0);
	BOOST_CHECK(t.size() == 1);
	BOOST_CHECK(t.count_node() == 3);
}

BOOST_AUTO_TEST_CASE(erase_iterator)
{
	boost::tries::trie_map<char, int> t;
	std::string s = "aaa", s1 = "aaaa", s2 = "aab", s3 = "bbb";
	t[s] = 1;
	t[s1] = 2;
	t[s2] = 3;
	t[s3] = 4;
	int node_cnt = t.count_node();
	BOOST_CHECK(t.size() == 4);
	std::cout << t.size() << ' ' << t.count_node() << std::endl;
	BOOST_CHECK(t.count_node() == node_cnt);
	std::cout << *t.begin() << std::endl;
	boost::tries::trie_map<char, int>::iterator ti;
	ti = t.begin();
	t.erase(t.begin());
	ti = t.begin();
	BOOST_CHECK(t.size() == 3);
	BOOST_CHECK(t.count_node() == 8);
	BOOST_CHECK(*ti == 2);
	t.erase(ti);
	BOOST_CHECK(t.size() == 2);
	ti = t.begin();
	BOOST_CHECK(*ti == 3);
	BOOST_CHECK(t.count_node() == 6);
	BOOST_CHECK(t[s] == 0);
	ti = t.begin();
	BOOST_CHECK(t.size() == 3);
	BOOST_CHECK(*ti == 0);
	BOOST_CHECK(t.count_node() == 7);
}

BOOST_AUTO_TEST_CASE(erase_key)
{
	boost::tries::trie_map<char, int> t;
	std::string s = "aaa", s1 = "aaaa", s2 = "aab", s3 = "bbb";
	t[s] = 1;
	t[s1] = 2;
	t[s2] = 3;
	t[s3] = 4;
	int node_cnt = t.count_node();
	BOOST_CHECK(t.size() == 4);
	std::cout << t.size() << ' ' << t.count_node() << std::endl;
	BOOST_CHECK(t.count_node() == node_cnt);
	std::cout << *t.begin() << std::endl;
	boost::tries::trie_map<char, int>::iterator ti;
	ti = t.begin();
	t.erase(s);
	ti = t.begin();
	BOOST_CHECK(t.size() == 3);
	BOOST_CHECK(t.count_node() == 8);
	BOOST_CHECK(*ti == 2);
	t.erase(s1);
	BOOST_CHECK(t.size() == 2);
	ti = t.begin();
	BOOST_CHECK(*ti == 3);
	BOOST_CHECK(t.count_node() == 6);
	BOOST_CHECK(t[s] == 0);
	ti = t.begin();
	BOOST_CHECK(t.size() == 3);
	BOOST_CHECK(*ti == 0);
	BOOST_CHECK(t.count_node() == 7);
	t.erase(std::string("bababa"));
	ti = t.begin();
	BOOST_CHECK(t.size() == 3);
	BOOST_CHECK(*ti == 0);
	BOOST_CHECK(t.count_node() == 7);
}

BOOST_AUTO_TEST_CASE(find_prefix)
{
	tci t;
	std::string s = "aaa", s1 = "aaaa", s2 = "aab", s3 = "bbb";
	t[s] = 1;
	t[s1] = 2;
	t[s2] = 3;
	t[s3] = 4;
	tci::iterator_range r = t.find_prefix(std::string("a"));
	// the statement is tested when I know r.second != t.end()
	std::cout << *r.first << " " << *r.second << std::endl;
	BOOST_CHECK(*r.second == 4);
	int j = 1;
	for (tci::iterator i = r.first; i != r.second; ++i)
	{
		std::cout << *i << std::endl;
		BOOST_CHECK(*i == j);
		++j;
	}
	r = t.find_prefix(std::string("aa"));
	std::cout << *r.first << " " << *r.second << std::endl;
	BOOST_CHECK(*r.second == 4);
	j = 1;
	for (tci::iterator i = r.first; i != r.second; ++i)
	{
		std::cout << *i << std::endl;
		BOOST_CHECK(*i == j);
		++j;
	}
	r = t.find_prefix(std::string("aaa"));
	std::cout << *r.first << " " << *r.second << std::endl;
	BOOST_CHECK(*r.second == 3);
	j = 1;
	for (tci::iterator i = r.first; i != r.second; ++i)
	{
		std::cout << *i << std::endl;
		BOOST_CHECK(*i == j);
		++j;
	}
	r = t.find_prefix(std::string("b"));
	//std::cout << *r.first << " " << *r.second << std::endl;
	BOOST_CHECK(r.second == t.end());
	for (tci::iterator i = r.first; i != r.second; ++i)
	{
		std::cout << *i << std::endl;
		BOOST_CHECK(*i == 4);
	}
	r = t.find_prefix(std::string("bbbbb"));
	//std::cout << *r.first << " " << *r.second << std::endl;
	BOOST_CHECK(r.second == t.end());
	for (tci::iterator i = r.first; i != r.second; ++i)
	{
		std::cout << *i << std::endl;
		BOOST_CHECK(*i == 1);
	}
}

BOOST_AUTO_TEST_CASE(get_key_test)
{
	tci t;
	std::string s = "aaa", s1 = "aaaa", s2 = "aab", s3 = "bbb";
	t[s] = 1;
	t[s1] = 2;
	t[s2] = 3;
	t[s3] = 4;
	tci t2;
	tci::iterator i = t.begin();
	t2[i.get_key()] = 1;
	++i;
	t2[i.get_key()] = 2;
	++i;
	t2[i.get_key()] = 3;
	++i;
	t2[i.get_key()] = 4;
	tci::iterator j = t2.begin();
	for (i = t.begin(); i != t.end(); ++i, ++j)
	{
		BOOST_CHECK(*i == *j);
		BOOST_CHECK(i.get_key() == j.get_key());
	}
	j = t2.erase(s2);
	BOOST_CHECK(*j == 4);
}
*/
BOOST_AUTO_TEST_SUITE_END()

