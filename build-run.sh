#!/usr/bin/env bash

set -euo pipefail

cmake -B build -DCMAKE_BUILD_TYPE=Debug -G Ninja
cmake --build build --parallel
./build/ledmatrix-cpp-test
