#!/bin/bash
export CRASHPAD_CHECKOUT_DIR=${CRASHPAD_CHECKOUT_DIR:-"$HOME/Desktop/github/crashpad"}
export CRASHPAD_BUILD_DIR=${CRASHPAD_BUILD_DIR:-"$CRASHPAD_CHECKOUT_DIR/out/Default"}
export PROJECT_DIR=${PROJECT_DIR:-"$HOME/Desktop/github/my-ubuntu-crasher"}
export CRASHPAD_DIR=${CRASHPAD_DIR:-"$PROJECT_DIR/crashpad"}
export OUT_DIR=${OUT_DIR:-"$PROJECT_DIR/out"}
export MODULE_NAME=${MODULE_NAME:-"myUbuntuCrasher"}
export BUGSPLAT_DATABASE=${BUGSPLAT_DATABASE:-"fred"}
export BUGSPLAT_APP_NAME=${BUGSPLAT_APP_NAME:-"myUbuntuCrasher"}
export BUGSPLAT_APP_VERSION=${BUGSPLAT_APP_VERSION:-"1.0.0"}
