#include <vector>
#include <algorithm>

class ip_lex_compare
{
	static bool byte_compare(const std::string &a, const std::string &b)
	{
		return std::stoi(a) > std::stoi(b);
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
	for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
	{
		if (lambda(*ip)) ip_filtered.push_back(*ip);
	}
	return ip_filtered;
}

template<typename ... Args>
auto first_n_bytes_lambda(Args ... args)
{
	return [=](const auto &ip) -> bool {
		std::vector<int> args_unpack{args...};
		auto limit = sizeof...(args) > ip.size() ? ip.size() : sizeof...(args);
		
		for (decltype(limit) i = 0; i < limit; ++i)
			if (std::stoi(ip[i]) != args_unpack[i]) return false;

		return true;
	};
}

auto any_byte_lambda(int byte)
{
	return [=](const auto &ip) -> bool {
		for (auto ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part)
			if (std::stoi(*ip_part) == byte)
				return true;

		return false;
	};
}
