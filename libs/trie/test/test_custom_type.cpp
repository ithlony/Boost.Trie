#define BOOST_TEST_MODULE trie_test
#include <boost/test/unit_test.hpp>
#include "boost/trie/trie.hpp"
#include "boost/trie/trie_map.hpp"
#include <string>
#include <iostream>

BOOST_AUTO_TEST_SUITE(trie_test)

class mytype {

public:
	explicit mytype() : value(0)
	{}

	mytype(int x) : value(x)
	{
	}

	mytype& operator=(const mytype& x)
	{
		value = x.value;
		return *this;
	}

	bool operator<(const mytype& x) const
	{
		return value < x.value;
	}
	bool operator==(const mytype& x) const
	{
		return value == x.value;
	}

	int value;
};

typedef boost::tries::trie_map<mytype, mytype> tmm;
typedef std::vector<mytype> vm;

std::ostream& operator<<(std::ostream& out, const mytype& m)
{
	out << m.value;
	return out;
}

mytype ms1[] = {1, 2, 3, 4};
mytype ms2[] = {1, 2, 2, 4};
mytype ms3[] = {2, 2, 4, 4};
mytype ms4[] = {2, 2, 3, 4};
vm s(ms1, ms1 + 2);
vm s1(ms1, ms1 + 4);
vm s2(ms2, ms2 + 4);
vm s3(ms3, ms3 + 4);
vm s4(ms4, ms4 + 4);
vm s5(ms4, ms4 + 2);

BOOST_AUTO_TEST_CASE(operator_test)
{
	tmm t;
	std::cout << t.count_node() + 100 << std::endl;
	vm s;
	s.push_back(mytype(1));
	s.push_back(mytype(2));
	s.push_back(mytype(3));
	vm s2;
	s2.push_back(mytype(2));
	std::cout << t.count_node() + 100 << std::endl;
	t[s] = 1;
	std::cout << t.count_node() + 100 << std::endl;
	BOOST_CHECK(t[s] == 1);
	t[s] = 5;
	std::cout << t.count_node() << std::endl;
	BOOST_CHECK(t[s] == mytype(5));
	t[s2] = t[s];
	std::cout << t.count_node() << std::endl;
	BOOST_CHECK(t.count_node() == 4);
	BOOST_CHECK(t[s] == t[s2]);
	BOOST_CHECK(t.count_node() == 4);
	BOOST_CHECK(*t.begin() == mytype(5));
	BOOST_CHECK(t.size() == 2);
	BOOST_CHECK(t.count_node() == 4);
	std::cout << t.count_node() << std::endl;
}

BOOST_AUTO_TEST_CASE(insert_and_find_test)
{
	tmm t;
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
	tmm t, t2;
	t[s] = 1; t[s1] = 2; t[s2] = 3; t[s3] = 4;
	t2 = t;
	std::cout <<t[s]<<std::endl;
	size_t node_cnt = 4 + 2 + 4;
	BOOST_CHECK(t2.size() == 4);
	BOOST_CHECK(t2.count_node() == node_cnt);
	std::cout <<t[s]<<std::endl;
	std::cout<< t2[s] << std::endl;
	BOOST_CHECK(t2[s] == 1);
	BOOST_CHECK(t2[s1] == 2);
	BOOST_CHECK(t2[s2] == 3);
	BOOST_CHECK(t2[s3] == 4);
	tmm t3(t2);
	BOOST_CHECK(t3.size() == 4);
	BOOST_CHECK(t3.count_node() == node_cnt);
	BOOST_CHECK(*t3.find(s) == 1);
	BOOST_CHECK(*t3.find(s1) == 2);
	BOOST_CHECK(*t3.find(s2) == 3);
	BOOST_CHECK(*t3.find(s3) == 4);
	BOOST_CHECK(t3.find(ms1, ms1 + 3) == t3.end());
	BOOST_CHECK(t3.find(ms1, ms1 + 4) != t3.end());
}

BOOST_AUTO_TEST_CASE(iterator_operator_plus)
{
	tmm t;
	BOOST_CHECK(t.empty() == true);
	BOOST_CHECK(t.size() == 0);
	std::cout <<"ddd"<<std::endl;
	BOOST_CHECK(t.begin() == t.end());
	std::cout <<"ddd"<<std::endl;
	t[s] = 1;
	t[s1] = 2;
	t[s2] = 3;
	BOOST_CHECK(t.begin() != t.end());
	std::cout <<"ddd"<<std::endl;
	tmm::iterator ti;
	ti = t.begin();
	BOOST_CHECK(*ti == 1);
	++ti;
	BOOST_CHECK(*ti == 3);
	BOOST_CHECK(t[s2] == 3);
	++ti;
	BOOST_CHECK(*ti == 2);
	++ti;
	BOOST_CHECK(ti == t.end());
	// test ++end()
	++ti;
	BOOST_CHECK(ti == t.end());
}

BOOST_AUTO_TEST_CASE(iterator_operator_minus)
{
	tmm t;
	BOOST_CHECK(t.empty() == true);
	BOOST_CHECK(t.size() == 0);
	BOOST_CHECK(t.begin() == t.end());
	t[s] = 1;
	t[s1] = 2;
	t[s2] = 3;
	BOOST_CHECK(t.begin() != t.end());
	tmm::iterator ti;
	tmm::const_iterator cti(t.end());
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
	BOOST_CHECK(*ti == 2);
	t[s3] = 4;
	++ti;
	BOOST_CHECK(*ti == 4);
	++ti;
	BOOST_CHECK(ti == t.end());
	++ti;
	BOOST_CHECK(ti == t.end());
	--ti;
	BOOST_CHECK(*ti == 4);
	int node_cnt = 4 + 2 + 4 + 2;
	t[s4] = 5;
	t[s5] = 6;
	BOOST_CHECK(t.count_node() == node_cnt);
	BOOST_CHECK(t.size() == 6);
}

BOOST_AUTO_TEST_CASE(clear)
{
	tmm t;
	t[s] = t[s1] = t[s2] = t[s3] = 10;
	int node_cnt = t.count_node();
	BOOST_CHECK(t.size() == 4);
	BOOST_CHECK(t.count_node() == node_cnt);
	t.clear();
	BOOST_CHECK(t.size() == 0);
	BOOST_CHECK(t.count_node() == 0);
	BOOST_CHECK(t[s] == 0);
	BOOST_CHECK(t.size() == 1);
	BOOST_CHECK(t.count_node() == 2);
}

BOOST_AUTO_TEST_CASE(erase_iterator)
{
	tmm t;
	t[s] = 1;
	t[s1] = 2;
	t[s2] = 3;
	t[s3] = 4;
	int node_cnt = t.count_node();
	BOOST_CHECK(t.size() == 4);
	BOOST_CHECK(t.count_node() == node_cnt);
	tmm::iterator ti;
	ti = t.begin();
	t.erase(t.begin());
	ti = t.begin();
	BOOST_CHECK(t.size() == 3);
	//std::cout << t.count_node() << std::endl;
	BOOST_CHECK(t.count_node() == node_cnt);
	BOOST_CHECK(*ti == 3);
	t.erase(ti);
	BOOST_CHECK(t.size() == 2);
	ti = t.begin();
	BOOST_CHECK(*ti == 2);
	BOOST_CHECK(t.count_node() == 8);
	BOOST_CHECK(t[s] == 0);
	ti = t.begin();
	BOOST_CHECK(t.size() == 3);
	BOOST_CHECK(*ti == 0);
	BOOST_CHECK(t.count_node() == 8);
}

BOOST_AUTO_TEST_CASE(erase_key)
{
	tmm t;
	t[s] = 1;
	t[s1] = 2;
	t[s2] = 3;
	t[s3] = 4;
	int node_cnt = t.count_node();
	BOOST_CHECK(t.size() == 4);
	BOOST_CHECK(t.count_node() == node_cnt);
	tmm::iterator ti;
	ti = t.begin();
	t.erase(ms1, ms1 + 1);
	ti = t.begin();
	// erasion failure
	BOOST_CHECK(t.size() == 4);
	BOOST_CHECK(*ti == 1);
	t.erase(ms1, ms1 + 2);
	ti = t.begin();
	BOOST_CHECK(t.size() == 3);
	BOOST_CHECK(*ti == 3);
	t.erase(s1);
	BOOST_CHECK(t.size() == 2);
	ti = t.begin();
	BOOST_CHECK(*ti == 3);
	BOOST_CHECK(t[s] == 0);
	ti = t.begin();
	BOOST_CHECK(t.size() == 3);
	BOOST_CHECK(*ti == 0);
	ti = t.begin();
	BOOST_CHECK(t.size() == 3);
	BOOST_CHECK(*ti == 0);
}

BOOST_AUTO_TEST_SUITE_END()
