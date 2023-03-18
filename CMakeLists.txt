cmake_minimum_required(VERSION 3.0.0)
project(Helmod2 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Helmod2 
src/main.cpp
src/Ingredient.hpp
src/ProductionLine.hpp
src/ProductionLine.cpp
src/nlohmann/json.hpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
