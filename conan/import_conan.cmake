if(CONAN_EXPORTED)
  message(Conan mode)
else()
  message(Standalone mode)

  list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
  list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

  if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(
      DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake"
      EXPECTED_HASH SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484 TLS_VERIFY ON
    )
  endif()

  include(${CMAKE_BINARY_DIR}/conan.cmake)
  conan_cmake_run(
    CONANFILE ${CMAKE_SOURCE_DIR}/conanfile.py # or relative build/conanfile.txt
    BASIC_SETUP
    CMAKE_TARGETS
    BUILD missing
  )

  conan_cmake_configure(GENERATORS cmake)
  conan_cmake_autodetect(settings)
  conan_cmake_install(
    PATH_OR_REFERENCE
    ${CMAKE_SOURCE_DIR}
    BUILD
    missing
    REMOTE
    conancenter
    SETTINGS
    ${settings}
  )
endif()
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
