#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
from conans import ConanFile, tools, CMake

class NanoIdXXConan(ConanFile):
    name = "nanoidxx"
    version = "0.1"
    
    description = "A tiny, URL-friendly, unique string ID generator for C++, implementation of ai's nanoid!"
    url = "https://github.com/pss146/nanoidxx"
    homepage = "https://github.com/pss146/nanoidxx"
    author = "Stanislav Perepelitsyn <stas.perepel@gmail.com>"
    license = "MIT"
    
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"

    def export_sources(self):
        self.copy("*")  # -> copies all files/folders from working dir into a “source” directory

    def requirements(self):
      self.requires.add("catch2/2.13.7")
    
    def configure_cmake(self):
        cmake = CMake(self)
        cmake.configure()
        return cmake

    def build(self):
        cmake = self.configure_cmake()
        cmake.build()
        cmake.test()

    def package(self):
        # Copy headers to the include folder and libraries to the lib folder
        self.copy("*.h", dst="include", src="include")

    def package_id(self):
        self.info.header_only()