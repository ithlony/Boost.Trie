#define BOOST_TEST_MODULE trie_test
#include <boost/test/unit_test.hpp>
#include "boost/trie/trie.hpp"
#include "boost/trie/trie_map.hpp"
#include <string>
#include <iostream>
#include <map>

BOOST_AUTO_TEST_SUITE(trie_test__mentor_antony)

BOOST_AUTO_TEST_CASE(default_construction_and_destruction)
{
    boost::tries::trie_map<std::string, std::string> t;
    (void)t;
}

class no_default_constructor_type {
    explicit no_default_constructor_type(int /*i*/){}
};

//@ Does not compile. However it MUST!
BOOST_AUTO_TEST_CASE(no_default_constructor_key)
{
	std::map<no_default_constructor_type, int> t;
	(void)t;
	/*
    boost::tries::trie_map<no_default_constructor_type, int> t;
    (void)t;
	*/
}

class counter_type {
    static int m_counts_constructed;
    static int m_counts_deleted;

    int m_value;
    int m_deleted;
public:
    static void reset() {
        m_counts_constructed = 0;
        m_counts_deleted = 0;
    }

    static int counts_constructed() { return m_counts_constructed; }
    static int counts_deleted() { return m_counts_deleted; }
    static int counts_alive() { return m_counts_constructed - m_counts_deleted; }

    counter_type() : m_value(-1), m_deleted(0) { ++ m_counts_constructed; }
    counter_type(int value) : m_value(value), m_deleted(0) { ++ m_counts_constructed; }
    counter_type(const counter_type& ct) : m_value(ct.m_value), m_deleted(0) { ++ m_counts_constructed; }

    ~counter_type() {
        ++ m_deleted;
        BOOST_CHECK_EQUAL(m_deleted, 1);
        ++ m_counts_deleted;
    }

    int value() const { return m_value; }
};


int counter_type::m_counts_constructed = 0;
int counter_type::m_counts_deleted = 0;

inline bool operator< (const counter_type& v1, const counter_type& v2) {
    return v1.value() < v2.value();
}

BOOST_AUTO_TEST_CASE(counting_constructions_and_destructions_key)
{
    counter_type::reset();
    std::vector<counter_type> data;
    data.push_back(counter_type(0));
    data.push_back(counter_type(0));
    data.push_back(counter_type(1));
    data.push_back(counter_type(2));
    data.push_back(counter_type(3));
    const int data_size = static_cast<int>(data.size());
    BOOST_CHECK_EQUAL(counter_type::counts_alive(), data_size);

    boost::tries::trie_map<counter_type, int> t;
	std::cout << counter_type::counts_alive() << std::endl;
    t.insert(data, 0);
	std::cout << counter_type::counts_alive() << std::endl;
    BOOST_CHECK_EQUAL(counter_type::counts_alive(), data_size * 2);

    t.insert(data, 0);
    BOOST_CHECK_EQUAL(counter_type::counts_alive(), data_size * 2);

    t.insert(data.begin(), data.end(), 0);
    BOOST_CHECK_EQUAL(counter_type::counts_alive(), data_size * 2);

    t.insert(data.begin() + 1, data.end(), 0);
    //BOOST_CHECK_EQUAL(counter_type::counts_alive(), data_size * 3 - 1);
	//the following statement is the correct one
    BOOST_CHECK_EQUAL(counter_type::counts_alive(), data_size * 3 - 2);

    t.clear();
    BOOST_CHECK_EQUAL(counter_type::counts_alive(), data_size);
}

BOOST_AUTO_TEST_CASE(counting_alive_equal_keys)
{
    counter_type::reset();
    // Inserting 25 elements with value 0
    std::vector<counter_type> data(25,counter_type(0));
    const int data_size = static_cast<int>(data.size());

    boost::tries::trie_map<counter_type, int> t;
    t.insert(data, 0);
    BOOST_CHECK_EQUAL(counter_type::counts_alive(), data_size * 2);

    t.insert(data, 0);
    BOOST_CHECK_EQUAL(counter_type::counts_alive(), data_size * 2);

    std::vector<counter_type>::const_iterator it = data.begin(),
            end = data.end();
    for (; it != end; ++it)
    {
        t.insert(it, end, 0);
        BOOST_CHECK_EQUAL(counter_type::counts_alive(), data_size * 2);
    }
}

BOOST_AUTO_TEST_SUITE_END()
