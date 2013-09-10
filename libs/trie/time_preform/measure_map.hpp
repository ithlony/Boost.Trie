#include <vector>
#include <cassert>
#include <map>

class insert_into_map 
{
	public:
		std::string info()
		{
			return "insert into map";
		}
		template<class Key>
			void operator() (std::vector<Key>& a, std::map<Key, int>& t)
			{
				for (int i = 0; i < a.size(); ++i)
				{
					t[a[i]] = i;
				}
			}
};

class erase_from_map
{
	public:
		template<class Key>
			void operator() (std::vector<Key>& a, std::map<Key, int>& t)
			{
				for (int i = 0; i < a.size(); ++i)
				{
					t.erase(a[i]);
				}
			}
};

class find_from_map
{
	public:
		template<class Key>
			void operator() (std::vector<Key>& a, std::map<Key, int>& t)
			{
				for (int i = 0; i < a.size(); ++i)
				{
					assert(t.find(a[i]) != t.end());
				}
			}
};

class count_from_map
{
	public:
	template<class Key>
		void operator()(std::vector<Key>& a, std::map<Key, int>& t)
		{
			for (int i = 0; i < a.size(); ++i)
			{
				assert(t.count(a[i]) > 0);
			}
		}
};

class is_prefix
{
	public:
		template<class KeyContainer>
			bool operator()(const KeyContainer& prefix, const KeyContainer& x)
			{
				auto pi = prefix.begin(), xi = x.begin();
				for (; pi != prefix.end() && xi != x.end(); ++pi, ++xi)
					if (*xi != *pi)
						return false;
				return (pi == prefix.end());
			}
};

class erase_prefix_from_map
{
	public:
		template<class KeyContainer>
			void operator()(const KeyContainer& prefix, std::map<KeyContainer, int>& t)
			{
				auto i = t.lower_bound(prefix);
				while (i != t.end() && is_prefix()(prefix, i->first)) {
					i = t.erase(i); //returns the next element in c++11
				}
			}
};

class count_prefix_from_map
{
	public:
		template<class KeyContainer>
			void operator() (const KeyContainer& prefix, std::map<KeyContainer, int>& t)
			{
				auto i = t.lower_bound(prefix);
				int cnt = 0;
				while (i != t.end() && is_prefix()(prefix, i->first)) {
					++i;
					++cnt;
				}
#ifdef DEBUG
				if (cnt > 1)
					std::cout << cnt << std::endl;
#endif
			}
};

class handle_prefixes_map
{
	public:
		template<class KeyContainer, class KCContainer, class Op>
			void operator() (Op op, const KCContainer& prefixes, std::map<KeyContainer, int>& t)
			{
				for (int i = 0; i < prefixes.size(); ++i)
				{
					op()(prefixes[i], t);
				}
			}
};

//clear
//swap
//begin
//end
//rbegin
//rend

