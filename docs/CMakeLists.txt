find_package(Doxygen REQUIRED)

# Find all the public headers
get_target_property(CAT_CUTIFIER_PUBLIC_HEADER_DIR lbcompiler INTERFACE_INCLUDE_DIRECTORIES)
file(GLOB_RECURSE CAT_CUTIFIER_PUBLIC_HEADERS ${CAT_CUTIFIER_PUBLIC_HEADER_DIR}/*.h)

set(DOXYGEN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/doxygen)
file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})

#This will be the main output of our command
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)

add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
                   DEPENDS ${CAT_CUTIFIER_PUBLIC_HEADERS}
                   COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/docs/Doxyfile
                   WORKING_DIRECTORY ${DOXYGEN_OUTPUT_DIR}
                   MAIN_DEPENDENCY Doxyfile
                   COMMENT "Generating docs")

add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})
