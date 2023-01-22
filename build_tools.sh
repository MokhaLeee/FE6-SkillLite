#!/bin/sh

cd `dirname $0`

BASE_DIR=$(pwd)
EA_DIR=$BASE_DIR/tools/EventAssembler
FE6_DIR=$BASE_DIR/tools/fe6

# Update tools' submodules
git submodule update --init --recursive

# Build event-assembler
cd $EA_DIR && ./build.sh

# Build agbcc in for fe6 decomp
cp $BASE_DIR/fe6.gba $FE6_DIR/fe6-base.gba && \
    cd $FE6_DIR/tools && ./install-agbcc.sh && \
    cd $FE6_DIR && make

cd $BASE_DIR
