include(FetchContent)
FetchContent_Declare(gtest
  QUIET
  URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz
)
# configure build of googletest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

# Making an executable
file(GLOB_RECURSE TEST_CPP ${CMAKE_CURRENT_LIST_DIR} "*.cpp")
add_executable(
    unit_tests
    ${TEST_CPP}
  )

target_link_libraries(unit_tests
  PRIVATE
    lbcompiler
    gtest_main
    gmock_main
  )

# automatic discovery of unit tests
include(GoogleTest)
gtest_discover_tests(unit_tests
  PROPERTIES
    LABELS "unit"
  DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
    240
  )
