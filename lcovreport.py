from conans import ConanFile, CMake, tools
import os

class TestPackageConan(ConanFile):
    settings = "os", "compiler", "arch", "build_type"
    generators = "cmake"

    def build_requirements(self):
        self.build_requires("gtest/1.8.1@evf-third-party/latest")
        self.build_requires("lcov/1.14.0@evf-third-party/latest")

    def build(self):
        cmake = CMake(self)
        cmake.verbose = True        
        cmake.configure()
        cmake.build()

    def test(self):
        bin_path = os.path.join("bin", "test")
        self.run("%s --gtest_output=xml:tests.xml" % bin_path, run_environment=True)
        self.codecoverage()
    
    def codecoverage(self):
        lcov = os.path.join(self.deps_cpp_info["lcov"].bin_paths[0],"lcov")
        genhtml = os.path.join(self.deps_cpp_info["lcov"].bin_paths[0],"genhtml")
        self.run("%s --capture --directory . --output-file ../../coverage.info" % lcov)
        self.run("%s --remove ../../coverage.info -o ../../coverage.info" % lcov)
        self.run("%s ../../coverage.info --output-directory ../../coverager_results" % genhtml)