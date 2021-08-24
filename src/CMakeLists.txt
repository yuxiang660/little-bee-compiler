# Making a library
add_library(lbcompiler)

file(GLOB_RECURSE SRC_CPP ${CMAKE_CURRENT_LIST_DIR} "*.cpp")
file(GLOB_RECURSE SRC_HEADER ${CMAKE_CURRENT_LIST_DIR} "*.h")

target_sources(lbcompiler
  PRIVATE
    ${SRC_CPP}
  PUBLIC
    ${SRC_HEADER}
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
