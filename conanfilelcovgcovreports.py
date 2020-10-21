import os

from conans import ConanFile, AutoToolsBuildEnvironment, tools

class LcovConan(ConanFile):
    name = "lcov_installer"
    version = "1.14"
    license = "GPL"
    author = "Sri Janaki Balagam <srijanaki.balagam@zf.com>"
    url = "https://github.com/torfinnberset/conan-lcov-installer"
…
            env_build = AutoToolsBuildEnvironment(self)
            env_build.make(target="install")

    def package_info(self):
        self.env_info.PATH.append(os.path.join(self.package_folder, "bin"))
        self.output.success("Added lcov to $PATH")
