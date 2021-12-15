from conans import ConanFile, CMake


class TypelistUtilsConan(ConanFile):
    name = "typelist_utils"
    version = "0.0.1"

    # Optional metadata
    license = "MIT"
    author = "Leo Ghafari"
    url = "https://github.com/Yuki-cpp/typelist_utils"
    description = "Small header only library allowing to manipulate tuples as type lists"
    topics = ("C++20", "type list")

    exports_sources = "conan/*", "include/*", "CMakeLists.txt", "test/*"
    no_copy_source = True
    generators = "cmake"

    def build_requirements(self):
        self.test_requires("catch2/2.13.7")

    def build(self):  # this is not building a library, just tests
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.test()

    def package(self):
        self.copy("*.hpp")

    def package_id(self):
        self.info.header_only()
