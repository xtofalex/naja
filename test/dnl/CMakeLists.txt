INCLUDE(GoogleTest)

SET(dnl_tests
  DNLDBTest.cpp
)

ADD_EXECUTABLE(dnlTests ${dnl_tests})

TARGET_LINK_LIBRARIES(dnlTests naja_dnl snl_netlists gtest gmock gtest_main)

GTEST_DISCOVER_TESTS(dnlTests)