cmake_minimum_required(VERSION 3.2)
project(tic-tac-toe)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -mmacosx-version-min=13.0")

set(SOURCE_FILES
  main.cpp
  resource_manager.cpp
  game_state.cpp
  render_engine.cpp
)
add_executable(tic-tac-toe ${SOURCE_FILES})    

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
  
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})      
  target_link_libraries(tic-tac-toe ${SFML_LIBRARIES})
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/image.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/arial.ttf
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})