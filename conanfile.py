from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
import aocd
import os

class AdventOfCode2024(ConanFile):
    name = "aoc_2025"
    version = "0.0.1"
    settings = "os", "compiler", "build_type", "arch"
    package_type = "application"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*"

    def requirements(self):
        self.requires("aoc_utils/[~1]")
        self.requires("ctre/[*]")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()
        
        year = 2025
        for day in range(1, 2 ):
            inputFileName = os.path.join( self.source_folder, "src", "Day{:02d}".format(day), "input.txt" )
            print( inputFileName )
            fh = open( inputFileName, "w" )
            try:
                fh.write( aocd.get_data(day=day, year=year) )
            except:
                print(f"Couldn't get input data for day {day}")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
            
    