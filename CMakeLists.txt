cmake_minimum_required(VERSION 3.2)
project(tic-tac-toe)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

if(WIN32)
  message("https://cmake.org/cmake/help/latest/variable/WIN32.html?highlight=win32")
elseif(APPLE)
  message("https://cmake.org/cmake/help/latest/variable/APPLE.html?highlight=apple")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmacosx-version-min=13.0")
elseif(UNIX)
  message("https://cmake.org/cmake/help/latest/variable/UNIX.html?highlight=unix")
endif()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)

set(MAIN_SOURCE_FILES
  main.cpp
  resource_manager.cpp
  game_state.cpp
  render_engine.cpp
  controller.cpp
  alpha_beta.cpp
)
add_executable(tic-tac-toe ${MAIN_SOURCE_FILES})    
if (SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(tic-tac-toe ${SFML_LIBRARIES})
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resource
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(googletest)

include(CTest)
add_subdirectory(tests)
