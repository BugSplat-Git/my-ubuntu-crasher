#!/bin/bash
source exports.sh

# Copy bin
cp $CRASHPAD_BUILD_DIR/crashpad_handler $CRASHPAD_DIR/bin

# Copy lib
cp $CRASHPAD_BUILD_DIR/obj/client/libclient.a $CRASHPAD_DIR/lib/libclient.a
cp $CRASHPAD_BUILD_DIR/obj/util/libutil.a $CRASHPAD_DIR/lib/libutil.a
cp $CRASHPAD_BUILD_DIR/obj/third_party/mini_chromium/mini_chromium/base/libbase.a $CRASHPAD_DIR/lib/libbase.a

# Copy include
cp -rf $CRASHPAD_CHECKOUT_DIR/* $CRASHPAD_DIR/include

# Tidy up include
find $CRASHPAD_DIR/include/ -type f ! -name "*.h" -delete
find $CRASHPAD_DIR/include/* -empty -type d -delete
