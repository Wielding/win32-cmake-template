cmake_minimum_required(VERSION 3.20)
include(GoogleTest)

project(supportlib.tests)

enable_testing()

add_executable(
        supportlib.tests
        Support.Tests.cpp
)

target_link_libraries(supportlib.tests gtest gtest_main supportlib)

add_test(supportlib.tests supportlib.tests)

gtest_discover_tests(supportlib.tests)
