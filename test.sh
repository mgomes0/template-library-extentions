#! /bin/bash

set -e

cmake -S . -B build -DTLEX_BUILD_TESTS=ON
cmake --build build
ctest --test-dir build --output-on-failure
