#!/bin/sh

cd `dirname $0`

BASE_DIR=$(pwd)
TOOL_DIR=$BASE_DIR/tools
EA_DIR=$TOOL_DIR/EventAssembler
FE6_DIR=$TOOL_DIR/fe6

# Update tools' submodules
git submodule update --init --recursive

# Build event-assembler
cd $EA_DIR && ./build.sh

# Build and install agbcc
TEMP_DIR=$(mktemp -d)
git clone git@github.com:pret/agbcc.git $TEMP_DIR
cd $TEMP_DIR
git checkout origin/fix-dwarf-debug-line
./build.sh
./install.sh $BASE_DIR
./install.sh $FE6_DIR
rm -fr $TEMP_DIR

# Build agbcc in for fe6 decomp
cp $BASE_DIR/fe6.gba $FE6_DIR/fe6-base.gba && \
    cd $FE6_DIR && make

cd $BASE_DIR
