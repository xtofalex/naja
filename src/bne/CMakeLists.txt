# SPDX-FileCopyrightText: 2024 The Naja authors <https://github.com/xtofalex/naja/blob/main/AUTHORS>
#
# SPDX-License-Identifier: Apache-2.0

set(BNE_SOURCES
  BNE.cpp
)

set(BNE_HEADERS
  BNE.h
)

add_library(naja_bne SHARED ${BNE_SOURCES})

target_link_libraries(naja_bne PUBLIC naja_snl)
target_compile_options(naja_bne PRIVATE ${NAJA_CXX_WARNINGS}) 
#target_compile_definitions(naja_snl PRIVATE SNL_DESTROY_DEBUG)

set_target_properties(naja_bne PROPERTIES PUBLIC_HEADER "${BNE_HEADERS}")
install(TARGETS naja_bne LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION include) 