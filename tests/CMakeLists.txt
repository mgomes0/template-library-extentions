include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
)

# Do not install googletest alongside our library
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ── Helpers ───────────────────────────────────────────────────────────────────
function(tlex_add_test target)
    add_executable(${target} ${ARGN})
    target_link_libraries(${target} PRIVATE tlex::tlex GTest::gtest_main)
    target_compile_features(${target} PRIVATE cxx_std_17)
    include(GoogleTest)
    gtest_discover_tests(${target})
endfunction()

# ── Test targets ──────────────────────────────────────────────────────────────
tlex_add_test(vector_test      vector_test.cpp)
tlex_add_test(unique_ptr_test  unique_ptr_test.cpp)
tlex_add_test(shared_ptr_test  shared_ptr_test.cpp)
