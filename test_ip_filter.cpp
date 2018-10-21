#define BOOST_TEST_MODULE ip_filter_test_module

#include <vector>
#include <string>
#include "ip_filter_lib.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ip_filter_test_suite)

std::vector<std::vector<std::string>> v =
    {{"2","151","3","67"},
    {"1","44","5","99"},
    {"2","59","111","23"},
    {"67","5","10","11"}};

BOOST_AUTO_TEST_CASE(ip_filter_test_first_byte)
{
    auto res = filter_by_lambda(v, first_n_bytes_lambda(2));
    BOOST_CHECK(res.size() == 2 && res[0][0] == "2" && res[1][0] == "2");
    
    res = filter_by_lambda(v, first_n_bytes_lambda(1));
    BOOST_CHECK(res.size() == 1 && res[0][0] == "1");
}

BOOST_AUTO_TEST_CASE(ip_filter_test_first_n_bytes)
{
    BOOST_CHECK(filter_by_lambda(v, first_n_bytes_lambda(2, 44)).size() == 0);
    BOOST_CHECK(filter_by_lambda(v, first_n_bytes_lambda(2, 59)).size() == 1);
    BOOST_CHECK(filter_by_lambda(v, first_n_bytes_lambda(1, 44, 5)).size() == 1);
    BOOST_CHECK(filter_by_lambda(v, first_n_bytes_lambda(1, 2, 3, 4, 5)).size() == 0);
}

BOOST_AUTO_TEST_CASE(ip_filter_test_first_empty)
{
    BOOST_CHECK(filter_by_lambda(v, first_n_bytes_lambda()).size() == v.size());
}

BOOST_AUTO_TEST_CASE(ip_filter_test_any)
{
    BOOST_CHECK(filter_by_lambda(v, any_byte_lambda(2)).size() == 2);
    BOOST_CHECK(filter_by_lambda(v, any_byte_lambda(5)).size() == 2);
    BOOST_CHECK(filter_by_lambda(v, any_byte_lambda(110)).size() == 0);
}

BOOST_AUTO_TEST_CASE(ip_filter_test_order)
{
    BOOST_CHECK( ip_lex_compare()(v[0], v[2]));
    BOOST_CHECK(!ip_lex_compare()(v[1], v[3]));
}

BOOST_AUTO_TEST_SUITE_END()
