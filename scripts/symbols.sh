#!/bin/bash
source exports.sh

$CRASHPAD_DIR/tools/symbol-upload-linux -b $BUGSPLAT_DATABASE \
    -a $BUGSPLAT_APP_NAME \
    -v $BUGSPLAT_APP_VERSION \
    -u $BUGSPLAT_EMAIL \
    -p $BUGSPLAT_PASSWORD \
    -d $PROJECT_DIR/out \
    -f "{$MODULE_NAME,*.so.2}" \
    --dumpSyms

