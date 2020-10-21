from conans import ConanFile, CMake, tools, errors
import os

class RaspigtestexampleConan(ConanFile):
    license = "n/a"
    author = "Srinivas Pasupula"
    url = "https://dev.azure.com/ZFDevOpsPoc/AZP-006_SW4ZF_SW_Foundation/_git/swf-raspi-tutorial"
    description = "Sample unit test project for azure."
    topics = ("gtest", "raspberry", "armv7")
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    exports_sources = "*"
    requires = "gtest/1.8.1@evf-third-party/latest"

    def build_requirements(self):
        if self.settings.os == "Linux" and self.settings.arch == "armv7":
           self.build_requires("arm-linux-gnueabihf/8.3.0@raspi/stable") if self.settings.compiler.version == "8.3" else self.build_requires("arm-linux-gnueabihf/4.9.3@raspi/stable")

    def build(self):
        cmake = CMake(self)
        if self.settings.compiler == "gcc":
            cmake = CMake(self, generator="Unix Makefiles")

        conan_project_defines = [str('-D__APP_VERSION__=\\\"')+str(self.version)+str('\\\"')]

        if float(str(self.settings.compiler.version)) >= 5:
            conan_project_defines.append("-DUSE_CPP14_FEATURES")

        cmake.definitions["CONAN_PROJECT_DEFINES"] = ";".join(conan_project_defines)

        # Changes required for cross compilation
        if self.settings.os == "Linux" and self.settings.arch == "armv7":
            for name in self.deps_cpp_info.deps:
                print("#########################################" + name)
            if "arm-linux-gnueabihf" in self.deps_cpp_info.deps:
                # The toolchain version 8.3.0 has to be in /opt/cross-pi-gcc, since this version not location independent.
                if self.settings.compiler.version == "8.3":
                    if not os.path.isdir(os.path.join("/opt","cross-pi-gcc")):
                        os.mkdir(os.path.join("/opt","cross-pi-gcc"))

                    old_cwd = os.getcwd()
                    os.chdir(os.path.join("/opt","cross-pi-gcc"))
                    print("Installing tool chain to /opt/cross-pi-gcc/ directory...")
                    os.system("conan install arm-linux-gnueabihf/8.3.0@raspi/stable -pr swf_linux_to_arm_raspi -s compiler.version=" + str(self.settings.compiler.version))
                    print("Installing tool chain done!")
                    os.chdir(old_cwd)

                # Setting environment variables while will be used to get the tool chain.
                os.environ["RASPBERRYPI_TOOLCHAIN_PATH"] = self.raspberrypi_toolchain_path = os.path.join("/opt","cross-pi-gcc") if self.settings.compiler.version == "8.3" else str(self.deps_cpp_info["arm-linux-gnueabihf"].rootpath)
                os.environ["RASPBERRYPI_TARGET_HOST"] = self.raspberrypi_target_host = "arm-linux-gnueabihf"
            else:
                raise errors.ConanInvalidConfiguration("Raspberry Pi tool chain package not found in the dependencies list, which is required to proceed with the build!")

        cmake.verbose = True        
        cmake.configure(source_folder=".")
        cmake.build()

    def test(self):
        exec_name = "swf-raspi-tutorial" + "." + str(self.settings.os) + "." + str(self.settings.arch) + "-test"
        
        if (self.settings.arch) == "armv7":
            if "arm-linux-gnueabihf" in self.deps_cpp_info.deps:
                os.environ["QEMU_LD_PREFIX"] = os.path.join(self.raspberrypi_toolchain_path, self.raspberrypi_target_host)
            else:
                self.output.error("Raspberry pi toolchain path is not configured. Configure QEMU_LD_PREFIX to run the executable.")

        self.run(os.path.join(self.build_folder, "bin", exec_name), run_environment=True)
    
    
    lcov --capture --directory self.build_folder --output-file self.build_folder/main_coverage.info
    genhtml self.build_folder/main_coverage.info --output-directory out

        
