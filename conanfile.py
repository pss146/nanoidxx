#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
from conan import ConanFile
from conan.tools.files import copy
from conan.tools.cmake import cmake_layout, CMake

class NanoIdXXConan(ConanFile):
    name = "nanoidxx"
    version = "0.1"
    
    description = "A tiny, URL-friendly, unique string ID generator for C++, implementation of ai's nanoid!"
    url = "https://github.com/pss146/nanoidxx"
    homepage = "https://github.com/pss146/nanoidxx"
    author = "Stanislav Perepelitsyn <stas.perepel@gmail.com>"
    license = "MIT"
    
    settings = "os", "compiler", "build_type", "arch"

    exports_sources = "include/*", "tests/*"
    no_copy_source = True
    generators = "CMakeToolchain", "CMakeDeps"
    # Important, define the package_type
    package_type = "header-library"

    def requirements(self):
      self.requires("catch2/3.8.1")

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder="tests")
        cmake.build()
        cmake.test()

    def package(self):
        # This will also copy the "include" folder
        copy(self, "*.h", self.source_folder, self.package_folder)

    def package_info(self):
        # For header-only packages, libdirs and bindirs are not used
        # so it's necessary to set those as empty.
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []

    def package_id(self):
        self.info.clear()