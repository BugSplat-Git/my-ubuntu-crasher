#!/bin/bash
source exports.sh

mkdir -p $OUT_DIR
bash compile.sh
bash handler.sh
bash attachment.sh
bash symbols.sh
