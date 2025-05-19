#!/bin/bash
source ./exports.sh

# Compile the shared library
clang++ -fPIC -shared -Wl,-soname,libcrash.so.2 -o "${OUT_DIR}/libcrash.so.2" "${PROJECT_DIR}/crash.cpp" -g -Wl,--build-id 