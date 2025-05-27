cmake_minimum_required(VERSION 3.21)
project(nanoid)

set(CMAKE_CXX_STANDARD 17)

add_library(nanoid INTERFACE)
add_library(pss146::nanoid ALIAS nanoid)    # Alias

target_include_directories(nanoid INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )

### TESTS
enable_testing()
add_subdirectory(tests)
