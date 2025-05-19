#!/bin/bash
source exports.sh

mkdir -p $OUT_DIR
bash lib.sh
bash compile.sh
bash handler.sh
bash attachment.sh
bash symbols.sh
