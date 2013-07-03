#ifndef BOOST_TRIE_HPP
#define BOOST_TRIE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


#include <map>
#include <iterator>
#include <utility>
#include <cstdio>
#include <memory>

namespace boost { namespace tries {

namespace detail {

template <typename Key, typename Value,
		 class Compare>
struct trie_node {
//protected:
	typedef Key key_type;
	typedef key_type* key_ptr;
	typedef Value value_type;
	typedef value_type* value_ptr;
	typedef trie_node<key_type, value_type, Compare> node_type;
	typedef node_type* node_ptr;
	typedef std::map<key_type, node_ptr, Compare> children_type;
	typedef typename children_type::iterator child_iter;
	typedef std::allocator<Value> value_allocator; // is it necessary here?

	children_type child;

//public:
	value_ptr value; // use unique_ptr here?
	node_ptr parent;
	//child_iter child_iter_of_parent;
	size_t node_count;
	size_t value_count;

	value_ptr new_value()
	{
		return value_allocator::allocate();
	}

	void delete_value()
	{
		value_allocator::deallocate();
	}

	trie_node() : value(0), parent(0), node_count(0), value_count(0) 
	{
		child.clear();
	}

	void destroy()
	{
		for (child_iter ci(child.begin()); ci != child.end(); ++ci)
		{
			ci->second->destroy();
			delete ci->second;
		}
		child.clear();
		if (value)
		{
			delete value;
		}
	}

	~trie_node()
	{
		destroy();
	}
};

template <typename Key, typename Value, class Compare>
struct trie_iterator
{
	//typedef std::bidirectional_iterator_tag iterator_category;
	typedef Key key_type;
	typedef Value value_type;
	typedef value_type& ref;
	typedef value_type* ptr;
	typedef trie_iterator<Key, Value, Compare> iterator;
	typedef trie_node<Key, Value, Compare> node_type;
	typedef iterator self;
	typedef node_type *link_type;

	link_type node;

	trie_iterator() : node(0)
	{
	}

	trie_iterator(link_type x) : node(x)
	{
	}

	trie_iterator(const iterator &it): node(it.node)
	{
	}

	ref operator*() const 
	{
		return node->value;
	}
	ptr operator->() const
	{
		return &(operator*()); 
	}

	self& operator++() 
	{
		// increment
		return *this;
	}
	self& operator++(int)
	{
		self tmp = *this;
		// increment
		return tmp;
	}

	self& operator--()
	{
		// decrement
		return *this;
	}
	self& operator--(int)
	{
		self tmp = *this;
		// decrement
		return tmp;
	}
}; 

} // namespace detail

template <typename Key, typename Value,
		 class Compare>
class trie {
protected:
	typedef Key key_type;
	typedef Value value_type;
	typedef trie<key_type, value_type, Compare> trie_type;
	typedef detail::trie_node<key_type, value_type, Compare> node_type;
	typedef key_type * key_ptr;
	typedef node_type * node_ptr;
	typedef std::allocator< node_type > trie_node_allocator;
	typedef size_t size_type;

	node_ptr root;
	size_type node_count;
	size_type value_count;

	node_type new_node() 
	{
		return trie_node_allocator::allocate();
	}

	void delete_node(node_type p)
	{
		return trie_node_allocator::deallocate(p);
	}

	node_type& leftmost() const
	{
		// to be written
		return NULL;
	}

	node_type& rightmost() const
	{
		// to be written
		return NULL;
	}

public:
	// iterators still unavailable here
	
	trie() {
		root = new_node();
	}

	typedef detail::trie_iterator<Key, Value, Compare> iterator;

	iterator begin()
	{
		return leftmost();
	}

	iterator end()
	{
		return root;
	}

	bool clear()
	{
		return root->destroy();
	}

	size_t size() const
	{
		return value_count;
	}
	
	bool empty() const {
		return value_count == 0;
	}

	~trie()
	{
		clear();
		delete_node(root);
	}

};

template<typename Key, typename Value,
		class Compare = std::less<Key> >
class trie_map
{
	typedef trie<Key, Value, Compare> trie_type;
};

}} // boost::tries
#endif // BOOST_TRIE_HPP
