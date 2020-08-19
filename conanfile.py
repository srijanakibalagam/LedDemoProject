from conans import ConanFile, CMake, tools, errors
import os

class swfraspitutorialConan(ConanFile):
    name = "demo-led-status-indication"
    version = "1.0.0"
    license = "n/a"
    author = "Hendrik Schall"
    url = ""
    description = "demo-led-status-indication"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    exports_sources = "CMakeLists.txt", "src/*"

    def configure(self):
        if not str(self.settings.compiler.libcxx) == "libstdc++11":
            self.output.warn("!!!compiler.libcxx is not set to libstdc++11!!!")

        if  self.settings.os == "Windows":
            raise errors.ConanInvalidConfiguration("swf-raspi-tutorial is only supported for Linux")

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

        cmake.definitions["CONAN_PROJECT_DEFINES"] = ";".join(conan_project_defines);
        
        # Changes required for cross compilation
        if self.settings.os == "Linux" and self.settings.arch == "armv7":
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
        cmake.definitions["BINARY_NAME"] = self.getbinaryname()
        cmake.configure(source_folder=".")
        cmake.build()

    def package(self):
        self.copy(self.getbinaryname(), src=os.path.join("src", "bin"), dst="bin", keep_path=False)

        # Writing shell script file to run the cross compiled Raspberry Pi executable on linux directly.
        if self.settings.os == "Linux" and self.settings.arch == "armv7":
            run_cmd = "#!/bin/bash\nsource activate_run.sh\nexport QEMU_LD_PREFIX=" + str(self.deps_cpp_info["arm-linux-gnueabihf-lib"].rootpath) + "\n" + os.path.join("./bin", self.getbinaryname()) + " $1\n"
            f = open("run.sh", "w")
            f.write(run_cmd)
            f.close()

            # setting permissions
            #os.system("chmod 777 run.sh")

            self.copy("run.sh")

    def getbinaryname(self):
        return self.name + "." + str(self.settings.os) + "." + str(self.settings.arch)

    def deploy(self):
        self.copy("*")

