
add_executable(nanoid_test main.cpp nanoid_test.cpp generator_test.cpp)
target_link_libraries(nanoid_test ${CONAN_LIBS})
target_include_directories(nanoid_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/include)


include(CTest)
include(Catch)
catch_discover_tests(nanoid_test)
