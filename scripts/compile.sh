#!/bin/bash
source exports.sh

clang++ $PROJECT_DIR/main.cpp \
    $CRASHPAD_DIR/lib/libclient.a \
    $CRASHPAD_DIR/lib/libutil.a \
    $CRASHPAD_DIR/lib/libbase.a \
    -I$CRASHPAD_DIR/include \
    -I$CRASHPAD_DIR/include/third_party/mini_chromium/mini_chromium \
    -o$OUT_DIR/$MODULE_NAME \
    -g \
    -Wl,--build-id

