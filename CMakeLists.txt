cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(project)

# Ищем установленную библиотеку
find_package(Matplot++ REQUIRED)

add_executable(demo_exeshnik 
main.cpp
Genome.cpp
evo.cpp
dataconst.cpp)

target_link_libraries(demo_exeshnik PUBLIC Matplot++::matplot)

