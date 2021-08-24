# Making a library
file(GLOB_RECURSE SRC_CPP ${CMAKE_CURRENT_LIST_DIR} "*.cpp")
add_library(lbcompiler ${SRC_CPP})

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
