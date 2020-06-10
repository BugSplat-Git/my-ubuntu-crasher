#!/bin/bash
source exports.sh
export SYM_FILE=$OUT_DIR/$MODULE_NAME.sym

$CRASHPAD_DIR/tools/dump_syms $PROJECT_DIR/out/$MODULE_NAME > $SYM_FILE
$CRASHPAD_DIR/tools/sym_upload $SYM_FILE "https://octomore.bugsplat.com/post/bp/symbol/breakpadsymbols.php?appName=myUbuntuCrasher&appVer=1.0.0"