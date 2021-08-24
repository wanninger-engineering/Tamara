cmake_minimum_required(VERSION 3.7.2)
project (tamara)

enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

include_directories(include packages/include)

file(GLOB SOURCES "src/*.c")
file(GLOB PACK_SOURCES "packages/src/*.c")

add_definitions(-DLINUX -DPACKAGE_OS -DPACKAGE_CURL -DPACKAGE_FILE -DPACKAGE_MATH)

add_executable(tamara ${SOURCES} ${PACK_SOURCES})
target_link_libraries(tamara readline m curl)



file(GLOB STDLIB "stdlib/*.ta")
file(COPY ${STDLIB} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})


add_test(NAME conditionals_test COMMAND ./build/tamara "tests/conditionals.ta")
set_tests_properties(conditionals_test PROPERTIES
  FAIL_REGULAR_EXPRESSION "TEST FAILED"
)
add_test(NAME exception_test COMMAND ./build/tamara "tests/exceptionHandling.ta")
set_tests_properties(exception_test PROPERTIES
  FAIL_REGULAR_EXPRESSION "TEST FAILED"
)
add_test(NAME file_test COMMAND ./build/tamara "tests/fileIo.ta")
set_tests_properties(file_test PROPERTIES
  FAIL_REGULAR_EXPRESSION "TEST FAILED"
)
add_test(NAME math_test COMMAND ./build/tamara "tests/mathTest.ta")
set_tests_properties(math_test PROPERTIES
  FAIL_REGULAR_EXPRESSION "TEST FAILED"
)
add_test(NAME oop_test COMMAND ./build/tamara "tests/oop.ta")
set_tests_properties(oop_test PROPERTIES
  FAIL_REGULAR_EXPRESSION "TEST FAILED"
)
add_test(NAME scope_test COMMAND ./build/tamara "tests/scope.ta")
set_tests_properties(scope_test PROPERTIES
  FAIL_REGULAR_EXPRESSION "TEST FAILED"
)
