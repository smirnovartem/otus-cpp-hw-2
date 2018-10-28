#include <vector>
#include <string>
#include <algorithm>

class ip_lex_compare
{
	static bool byte_compare(const std::string &a, const std::string &b)
	{
		return a.size() > b.size() || (a.size() == b.size() && a > b);
	}
	public:
	bool operator()(const std::vector<std::string> &a, const std::vector<std::string> &b) const
	{
		return std::lexicographical_compare(a.cbegin(), a.cend(), b.cbegin(), b.cend(), byte_compare);
	}
}; 

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
		std::vector<std::string> args_unpack{args...};
		auto limit = sizeof...(args) > ip.size() ? ip.size() : sizeof...(args);
		
		for (decltype(limit) i = 0; i < limit; ++i)
			if (ip[i] != args_unpack[i]) return false;

		return true;
	};
}

auto any_byte_lambda(std::string byte)
{
	return [=](const auto &ip) -> bool {
		return std::find(ip.cbegin(), ip.cend(), byte) != ip.cend();
	};
}
