#!/bin/bash
source exports.sh

mkdir -p $OUT_DIR
bash compile.sh
bash symbols.sh