#include <boost/trie/trie_map.hpp>
#include <vector>
#include <cassert>
#include <map>

class insert_into_tmap{
	public:
		template<class Key, class KeyElement>
			void operator()(std::vector<Key>& a, boost::tries::trie_map<KeyElement, int>& t)
			{
				for (int i = 0; i < a.size(); ++i)
				{
					t[a[i]] = i;
				}
			}
};

class erase_from_tmap{
	public:
		template<class Key, class KeyElement>
			void operator()(std::vector<Key>& a, boost::tries::trie_map<KeyElement, int>& t)
			{
				for (int i = 0; i < a.size(); ++i)
				{
					t.erase(a[i]);
				}
			}
};

class find_from_tmap{
	public:
		template<class Key, class KeyElement>
			void operator()(std::vector<Key>& a, boost::tries::trie_map<KeyElement, int>& t)
			{
				for (int i = 0; i < a.size(); ++i)
				{
					assert(t.find(a[i]) != t.end());
				}
			}
};

class count_from_tmap{
	public:
		template<class Key, class KeyElement>
			void operator()(std::vector<Key>& a, boost::tries::trie_map<KeyElement, int>& t)
			{
				for (int i = 0; i < a.size(); ++i)
				{
					assert(t.count(a[i]) > 0);
				}
			}
};

class erase_prefix_from_tmap{
	public:
		template<class KeyContainer, class KeyElement>
			void operator()(const KeyContainer& prefix, boost::tries::trie_map<KeyElement, int>& t)
			{
				t.erase_prefix(prefix);
			}
};

class count_prefix_from_tmap{
	public:
		template<class KeyContainer, class KeyElement>
			void operator()(const KeyContainer& prefix, boost::tries::trie_map<KeyElement, int>& t)
			{
				int cnt = t.count_prefix(prefix);
#ifdef DEBUG
				if (cnt > 1)
					std::cout << cnt << std::endl;
#endif
			}
};


//clear
//swap
//begin
//end
//rbegin
//rend

