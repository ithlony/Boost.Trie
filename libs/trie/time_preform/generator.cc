#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int n;

void generator_strings()
{
	std::ofstream fout("strings.in");
	int char_range = 'z' - ' ';
	int leng_range = 50;
	std::vector<std::string> a;
	for (int i = 0; i < n; ++i)
	{
		int len = rand() % leng_range + 1;
		std::string s("");
		for (int j = 0; j < len; ++j)
		{
			char c = rand() % char_range + '!';
			s += c;
		}
		a.push_back(s);
		//fout << s << std::endl;
	}
	std::sort(a.begin(), a.end());
	for (int i = 0; i < a.size(); ++i)
		fout << a[i] << std::endl;
}

int main(int argc, char *argv[])
{ 
	if (argc != 2)
		return 0;
	sscanf(argv[1], "%d", &n);
	generator_strings();
	return 0;
}
