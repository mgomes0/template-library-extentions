cmake_minimum_required(VERSION 3.21)

project(
    template-library-extensions
    VERSION 0.1.0
    DESCRIPTION "A C++ header-only template library extensions"
    LANGUAGES CXX
)

# ── Library target ────────────────────────────────────────────────────────────
add_library(template-library-extensions INTERFACE)
add_library(tlex::tlex ALIAS template-library-extensions)

target_include_directories(
    template-library-extensions
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(template-library-extensions INTERFACE cxx_std_17)

# ── Install rules ─────────────────────────────────────────────────────────────
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(
    TARGETS template-library-extensions
    EXPORT  template-library-extensionsTargets
)

install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT template-library-extensionsTargets
    NAMESPACE tlex::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/template-library-extensions
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/template-library-extensionsConfigVersion.cmake"
    VERSION       ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/template-library-extensionsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/template-library-extensionsConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/template-library-extensions
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/template-library-extensionsConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/template-library-extensionsConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/template-library-extensions
)

# ── Tests ─────────────────────────────────────────────────────────────────────
option(TLEX_BUILD_TESTS "Build tests" OFF)

if(TLEX_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
