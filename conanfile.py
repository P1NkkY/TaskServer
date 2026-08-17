from conan import ConanFile
from conan.tools.cmake import cmake_layout

class TaskServer(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def configure(self) -> None:
        self.options["*"].shared = False
        self.options["*"].header_only = True
        self.options["boost*"].header_only = True

    def requirements(self):
        self.requires("boost/1.91.0")
        self.requires("gtest/1.18.0")

    def layout(self):
        cmake_layout(self)