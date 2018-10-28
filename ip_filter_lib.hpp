#include <vector>
#include <string>
#include <algorithm>

auto stoi_vector(const std::vector<std::string> &ip)
{
	std::vector<int> ip_int;
	ip_int.reserve(ip.size());
	std::transform(ip.cbegin(), ip.cend(),
					std::back_inserter(ip_int),
					[](const auto &byte){ return std::stoi(byte); }
	);
	return ip_int;
}

template<typename T, typename F>
auto filter_by_lambda(const T &ip_pool, F lambda)
{
	T ip_filtered;
	ip_filtered.reserve(ip_pool.size());
	std::copy_if(ip_pool.cbegin(), ip_pool.cend(), std::back_inserter(ip_filtered), lambda);
	return ip_filtered;
}

template<typename ... Args>
auto first_n_bytes_lambda(Args ... args)
{
	return [=](const auto &ip) -> bool {
		std::vector<int> args_unpack{args...};
		auto limit = sizeof...(args) > ip.size() ? ip.size() : sizeof...(args);
		
		for (decltype(limit) i = 0; i < limit; ++i)
			if (ip[i] != args_unpack[i]) return false;

		return true;
	};
}

auto any_byte_lambda(int byte)
{
	return [=](const auto &ip) -> bool {
		return std::find(ip.cbegin(), ip.cend(), byte) != ip.cend();
	};
}
