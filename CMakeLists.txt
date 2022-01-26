cmake_minimum_required(VERSION 3.21)
project(nanoid)

set(CMAKE_CXX_STANDARD 17)

### Conan integration
if (NOT EXISTS conanbuildinfo.cmake)
    message(FATAL_ERROR "Run Conan first: conan install <path_to_your_conanfile.txt>")
endif ()
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(nanoid INTERFACE)
add_library(pss146::nanoid ALIAS nanoid)    # Alias

target_link_libraries(nanoid ${CONAN_LIBS})

target_include_directories(nanoid INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )

### TESTS
enable_testing()
if (BUILD_TESTING)
    add_subdirectory(tests)
endif ()