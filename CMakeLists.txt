cmake_minimum_required(VERSION 3.10)
project(Graph VERSION 0.1.0 LANGUAGES CXX)

#include(CTest)
#enable_testing()

# add_executable(my_target graph.cpp)
# target_link_libraries(my_target PUBLIC matplot)

# add_executable(Graph graph.cpp)
#set_property(TARGET Graph PROPERTY CXX_STANDART 17)

# Ищем установленную библиотеку
find_package(Matplot++ REQUIRED)

add_executable(my_target graph.cpp)

# Линкуем правильным образом
target_link_libraries(my_target PUBLIC Matplot++::matplot)


