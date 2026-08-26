from conan import ConanFile
from conan.tools.cmake import cmake_layout

class TaskServer(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def configure(self) -> None:
        self.options["*"].shared = False

        # Настройка Boost
        boost = self.options["boost"]
        boost.without_math = True
        boost.without_stacktrace = True
        boost.without_test = True
        boost.without_graph = True
        boost.without_coroutine = True
        boost.without_contract = True
        boost.without_cobalt = True
        boost.without_wave = True
        boost.without_url = True
        boost.without_charconv = True
        boost.without_iostreams = True
        boost.without_locale = True
        boost.without_random = True
        boost.without_type_erasure = True

    def requirements(self):
        self.requires("boost/1.90.0")
        self.requires("gtest/1.18.0")

    def layout(self):
        cmake_layout(self)