cmake_minimum_required(VERSION 3.2)
project(tic-tac-toe-test)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -mmacosx-version-min=13.0")

include_directories(
  ../googletest/googletest/include
)

set(GAME_STATE_UNITTEST_SOURCE_FILES
  game_state_unittest.cpp
  ../game_state.cpp
)
add_executable(game_state_unittest ${GAME_STATE_UNITTEST_SOURCE_FILES})
target_link_libraries(game_state_unittest gtest gtest_main)
add_test(NAME game_state_unittest COMMAND game_state_unittest)
