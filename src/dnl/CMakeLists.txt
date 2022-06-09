set(SOURCES
  DNLInstance.cpp
  DNLEqui.cpp
  DNLDB.cpp
  DNLSNLConstructor.cpp
)

set(DNL_HEADERS
  DLNDB.h
)

add_library(naja_dnl SHARED ${SOURCES})
target_link_libraries(naja_dnl PUBLIC coverage_config naja_snl)
target_compile_options(naja_dnl PRIVATE ${NAJA_CXX_WARNINGS})
target_include_directories(naja_snl PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)
set_target_properties(naja_dnl PROPERTIES PUBLIC_HEADER "${DNL_HEADERS}")