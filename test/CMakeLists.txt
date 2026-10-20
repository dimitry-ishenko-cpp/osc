# test

add_executable(test_osc
    test_value.cpp
    test_message.cpp
    test_bundle.cpp
    test_dispatch.cpp
)
target_link_libraries(test_osc osc++::osc++ GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_osc)
