## How to build this demo

```bash
git clone https://github.com/bast/gtest-demo.git
cd gtest-demo
cmake -S. -Bbuild 
cmake --build build
```


## Running the tests

Either using `ctest`:
```
$ cd build
$ ctest

Running tests...
Test project /home/user/gtest-demo/build
    Start 1: unit
1/1 Test #1: unit .............................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec
```

Or directly using `unit_tests`:
```
$ cd build 
$ ./bin/unit_tests

[==========] Running 2 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 2 tests from example
[ RUN      ] example.add
[       OK ] example.add (0 ms)
[ RUN      ] example.subtract
[       OK ] example.subtract (0 ms)
[----------] 2 tests from example (1 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test case ran. (1 ms total)
[  PASSED  ] 2 tests.

```


## CMake Intro
* CMake Reference - https://cliutils.gitlab.io/modern-cmake/chapters/basics.html

### Setting a project
* [Wiki](https://cmake.org/cmake/help/latest/command/project.html?highlight=project)
```
project(<PROJECT-NAME> [<language-name>...])
project(<PROJECT-NAME>
        [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
        [DESCRIPTION <project-description-string>]
        [HOMEPAGE_URL <url-string>]
        [LANGUAGES <language-name>...])
```
* Example: [CMakeLists.txt](./CMakeLists.txt)
```
project(gtest-demo VERSION 1.0
                DESCRIPTION "C++ Start Up Project"
                LANGUAGES CXX)
```

### Making an executable
* [Wiki](https://cmake.org/cmake/help/latest/command/add_executable.html)
```
add_executable(<name> [WIN32] [MACOSX_BUNDLE]
               [EXCLUDE_FROM_ALL]
               [source1] [source2 ...])
```
* Example: [CMakeLists.txt](./test/CMakeLists.txt)
```
add_executable(
    unit_tests
    test_example.cpp
    test_hello.cpp
  )
```

### Making a library
* [Wiki](https://cmake.org/cmake/help/latest/command/add_library.html)
```
add_library(<name> [STATIC | SHARED | MODULE]
            [EXCLUDE_FROM_ALL]
            [<source>...])
```
* Example: [CMakeLists.txt](./src/CMakeLists.txt)
```
add_library(example)
```

### Targets Commands
* [target_include_directories](https://cmake.org/cmake/help/latest/command/target_include_directories.html)
```
target_include_directories(<target> [SYSTEM] [AFTER|BEFORE]
  <INTERFACE|PUBLIC|PRIVATE> [items1...]
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
```
* [target_link_libraries](https://cmake.org/cmake/help/latest/command/target_link_libraries.html)
```
target_link_libraries(<target> ... <item>... ...)
```