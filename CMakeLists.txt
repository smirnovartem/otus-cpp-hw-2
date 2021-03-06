cmake_minimum_required(VERSION 3.2)

project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(ip_filter main.cpp)

add_executable(test_ip_filter test_ip_filter.cpp)

set_target_properties(ip_filter test_ip_filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

set_target_properties(test_ip_filter PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(test_ip_filter
    ${Boost_LIBRARIES}
)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT $ENV{CONTACT_EMAIL})

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

enable_testing()

add_test(ip_filter_tests test_ip_filter)
