#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "ip_filter_lib.hpp"

auto split(const std::string &str, char d)
{
	std::vector<std::string> r;

	auto stop = str.find_first_of(d);
	decltype(stop) start = 0;
	while (stop != std::string::npos)
	{
		r.push_back(str.substr(start, stop - start));

		start = stop + 1;
		stop = str.find_first_of(d, start);
	}

	r.push_back(str.substr(start));

	return r;
}

void print_ip(const std::vector<std::vector<std::string>> &ip_pool)
{
	for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
	{
		for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
		{
			if (ip_part != ip->cbegin())
				std::cout << ".";
			std::cout << *ip_part;
		}
		std::cout << std::endl;
	}
}

int main(int argc, char const *argv[])
{
	try
	{
		std::vector<std::vector<std::string>> ip_pool;

		for (std::string line; std::getline(std::cin, line);)
		{
			auto v = split(line, '\t');
			ip_pool.push_back(split(v.at(0), '.'));
		}

		// reverse lexicographically sort
		std::sort(ip_pool.begin(), ip_pool.end(), ip_lex_compare());

		print_ip(ip_pool);

		// filter by first byte and output
		auto ip_filter_1 = filter_by_lambda(ip_pool, first_n_bytes_lambda(1));
		print_ip(ip_filter_1);

		// filter by first and second bytes and output
		auto ip_filter_2 = filter_by_lambda(ip_pool, first_n_bytes_lambda(46, 70));
		print_ip(ip_filter_2);

		// filter by any byte and output
		auto ip_filter_3 = filter_by_lambda(ip_pool, any_byte_lambda(46));
		print_ip(ip_filter_3);

	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
