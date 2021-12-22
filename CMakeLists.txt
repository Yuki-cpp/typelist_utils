cmake_minimum_required(VERSION 3.15)
project(typelist_utils CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(conan/import_conan.cmake)

add_executable(typelist_utils test/main.cpp test/test_utils.cpp test/test_sort.cpp)
target_include_directories(typelist_utils PRIVATE include ${CONAN_INCLUDE_DIRS})

if(ENABLE_COVERAGE)
  target_compile_options(
    typelist_utils
    PRIVATE
      -fprofile-instr-generate
      -fcoverage-mapping
      -mllvm
      -runtime-counter-relocation
  )

  target_link_options(
    typelist_utils
    PRIVATE
    -fprofile-instr-generate
    -fcoverage-mapping
  )
endif()

target_compile_options(
  typelist_utils
  PRIVATE
    -Wall
    -Wextra
    -pedantic
    -Werror
)
set(
  CTEST_COVERAGE_COMMAND
  "llvm-cov-13"
)
enable_testing()
add_test(
  NAME typelist_utils
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  COMMAND
    typelist_utils
)

install(DIRECTORY include/typelist_utils DESTINATION include)
