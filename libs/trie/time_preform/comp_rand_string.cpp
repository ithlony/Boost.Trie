#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include <cmath>
#include "measure_map.hpp"
#include "measure_trie_map.hpp"
#include <boost/timer/timer.hpp>

std::vector<std::string> vs;
class handle_prefixes
{
	public:
		template<class DataContainer, class Container, class Op>
			void operator() (Op op, const DataContainer& prefixes, Container& t)
			{
				for (int i = 0; i < prefixes.size(); ++i)
				{
					op(prefixes[i], t);
				}
			}
};

void read_data()
{
	std::ifstream fin("strings.in");
	std::string s;
	while (fin >> s)
	{
		vs.push_back(s);
	}
}
template<class Functor, class Param1, class Param2>
void infos(int rep_time, Functor func, Param1& vs, Param2& m)
{
	std::cout << typeid(func).name() << std::endl;
	std::cout << "repeat time: " << rep_time << std::endl;
	std::cout << "data size: " << vs.size() << std::endl;
}

template<class Functor, class Param1, class Param2>
void performance_profile(int rep_time, Functor func, Param1& vs, Param2& m)
{
	infos(rep_time, func, vs, m);
	boost::timer::auto_cpu_timer t(5, " %t sec CPU, %w sec real\n\n");
	for (int i = 0; i < rep_time; ++i)
		func(vs, m);
}

template<class Functor, class PFunctor, class Param1, class Param2>
void performance_profile(int rep_time, PFunctor pfunc, Functor func, Param1& vs, Param2& m)
{
	infos(rep_time, func, vs, m);
	boost::timer::auto_cpu_timer t(5, " %t sec CPU, %w sec real\n\n");
	for (int i = 0; i < rep_time; ++i)
		pfunc(func, vs, m);
}

int main()
{
	read_data();

	std::map<std::string, int> m;
	boost::tries::trie_map<char, int> tm;
	performance_profile(100, insert_into_map(), vs, m);
	performance_profile(100, insert_into_tmap(), vs, tm);
	performance_profile(100, find_from_map(), vs, m);
	performance_profile(100, find_from_tmap(), vs, tm);
	performance_profile(100, count_from_map(), vs, m);
	performance_profile(100, count_from_tmap(), vs, tm);
	performance_profile(100, count_prefix_from_map(), vs[0], m);
	performance_profile(100, count_prefix_from_tmap(), vs[0], tm);
	performance_profile(1, handle_prefixes(), count_prefix_from_map(), vs, m);
	performance_profile(1, handle_prefixes(), count_prefix_from_tmap(), vs, tm);

	return 0;
}
