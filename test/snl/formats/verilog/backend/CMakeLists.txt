include(GoogleTest)

set(snl_vrl_tests
    SNLVRLDumperTest0.cpp
    SNLVRLDumperTest1.cpp
    SNLVRLDumperTestTermNets.cpp
    SNLVRLDumperTestParameters.cpp
)

add_executable(snlVRLTests ${snl_vrl_tests})

target_compile_definitions(snlVRLTests PRIVATE
    SNL_VRL_DUMPER_TEST_PATH="${CMAKE_CURRENT_BINARY_DIR}"
    SNL_VRL_DUMPER_REFERENCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/references")
target_link_libraries(snlVRLTests naja_snl_verilog gtest gtest_main)

GTEST_DISCOVER_TESTS(snlVRLTests)
