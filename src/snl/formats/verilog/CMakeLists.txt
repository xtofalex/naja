set(SOURCES
  frontend/SNLVRLParser.cpp
  backend/SNLVRLDumper.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/thirdparty/Parser-Verilog/parser-verilog)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

BISON_TARGET(verilog_parser
             ${PROJECT_SOURCE_DIR}/thirdparty/Parser-Verilog/parser-verilog/verilog_parser.yy
             ${CMAKE_CURRENT_BINARY_DIR}/verilog_parser.tab.cc)
FLEX_TARGET(verilog_lexer
            ${PROJECT_SOURCE_DIR}/thirdparty/Parser-Verilog/parser-verilog/verilog_lexer.l
            ${CMAKE_CURRENT_BINARY_DIR}/verilog_lexer.yy.cc)
ADD_FLEX_BISON_DEPENDENCY(verilog_lexer verilog_parser)

add_library(naja_snl_verilog SHARED
  ${SOURCES}
  ${FLEX_verilog_lexer_OUTPUTS}
  ${BISON_verilog_parser_OUTPUTS}
)

target_link_libraries(naja_snl_verilog naja_snl)

target_include_directories(naja_snl_verilog PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/frontend
  ${CMAKE_CURRENT_SOURCE_DIR}/backend
)

add_executable(snlverilog SNLVerilog.cpp)
target_link_libraries(snlverilog naja_snl_verilog)