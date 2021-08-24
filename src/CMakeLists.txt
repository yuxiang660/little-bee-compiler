# Making a library
add_library(lbcompiler)

target_sources(lbcompiler
  PRIVATE
    lexer.cpp
  PUBLIC
    lexer.h
  )

target_include_directories(lbcompiler
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

# we use this to get code coverage
# flags are only valid with the GNU compiler and on Linux
if(CMAKE_CXX_COMPILER_ID MATCHES GNU AND CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
  target_compile_options(lbcompiler
    PUBLIC
      "--coverage"
    )
  target_link_options(lbcompiler
    INTERFACE
      "--coverage"
    )
endif()
