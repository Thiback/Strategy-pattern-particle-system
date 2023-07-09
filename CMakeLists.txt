cmake_minimum_required(VERSION 3.10)
project(MySFMLProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# find the SFML package
find_package(SFML 2.6 COMPONENTS system window graphics CONFIG REQUIRED)

# collect all the source files into variable
set(SOURCES main.cpp Game.hpp Button.hpp DrawStrategy.hpp Particle.hpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)