cmake_minimum_required(VERSION 3.21)

find_package(Catch2 REQUIRED)

add_executable(nanoid_test nanoid_test.cpp generator_test.cpp)
target_link_libraries(nanoid_test Catch2::Catch2WithMain)
#message(${CMAKE_CURRENT_SOURCE_DIR})
#message(${CMAKE_SOURCE_DIR})
#target_include_directories(nanoid_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/include)
target_include_directories(nanoid_test PRIVATE ../include)

include(CTest)
include(Catch)
catch_discover_tests(nanoid_test)
