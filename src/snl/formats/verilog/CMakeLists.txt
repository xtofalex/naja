set(SOURCES
  frontend/SNLVRLParser.cpp
  backend/SNLVRLDumper.cpp
)

add_library(naja_snl_verilog SHARED ${SOURCES})

target_link_libraries(naja_snl_verilog naja_snl verilog)

target_include_directories(naja_snl_verilog PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/frontend
  ${CMAKE_CURRENT_SOURCE_DIR}/backend
)

add_executable(snlverilog SNLVerilog.cpp)
target_link_libraries(snlverilog naja_snl_verilog)
