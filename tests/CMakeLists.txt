cmake_minimum_required(VERSION 3.2)
project(tic-tac-toe-test)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

if(WIN32)
  message("https://cmake.org/cmake/help/latest/variable/WIN32.html?highlight=win32")
elseif(APPLE)
  message("https://cmake.org/cmake/help/latest/variable/APPLE.html?highlight=apple")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmacosx-version-min=13.0")
elseif(UNIX)
  message("https://cmake.org/cmake/help/latest/variable/UNIX.html?highlight=unix")
endif()

include_directories(
  ../googletest/googletest/include
)

set(GAME_STATE_UNITTEST_SOURCE_FILES
  game_state_unittest.cpp
  ../game_state.cpp
  ../alpha_beta.cpp
)
add_executable(game_state_unittest ${GAME_STATE_UNITTEST_SOURCE_FILES})
target_link_libraries(game_state_unittest gtest gtest_main)
add_test(NAME game_state_unittest COMMAND game_state_unittest)
