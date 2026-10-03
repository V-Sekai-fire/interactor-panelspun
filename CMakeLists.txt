cmake_minimum_required(VERSION 3.24)
project(panelspun VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(PANELSPUN_BUILD_TESTS "Build the panelspun tests" ${PROJECT_IS_TOP_LEVEL})

add_library(panelspun STATIC
  src/split_tree.cpp
)
target_include_directories(panelspun PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
if(MSVC)
  target_compile_options(panelspun PRIVATE /W4 /permissive-)
else()
  target_compile_options(panelspun PRIVATE -Wall -Wextra)
endif()

if(PANELSPUN_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
