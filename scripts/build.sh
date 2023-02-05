#!/bin/bash

BUILD_TYPE=$1

if [ -z "$BUILD_TYPE" ]
then
    BUILD_TYPE=Debug
fi

SCRIPTS_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
REPO_DIR=$SCRIPTS_DIR/..
COMLINT_BUILD_DIR=$REPO_DIR/build
EXAMPLES_DIR=$REPO_DIR/examples
EXAMPLES_BUILD_DIR=$EXAMPLES_DIR/build

echo ----- Build type: $BUILD_TYPE -----

echo "----- Configuring CMake for ComlintCpp for sources in $REPO_DIR and build in $COMLINT_BUILD_DIR -----"
cmake -S $REPO_DIR -B $COMLINT_BUILD_DIR -DCMAKE_BUILD_TYPE=$BUILD_TYPE
echo "----- ComlintCpp CMake configuration done -----"

echo "----- Building ComlintCpp in $COMLINT_BUILD_DIR -----"
cmake --build $COMLINT_BUILD_DIR --config $BUILD_TYPE
echo "----- ComlintCpp build done -----"

echo "----- Installing ComlintCpp in $COMLINT_BUILD_DIR -----"
cmake --install $COMLINT_BUILD_DIR --config $BUILD_TYPE
echo "----- ComlintCpp installation done -----"

echo "----- Configuring CMake for Comlint examples for sources in $EXAMPLES_DIR and build in $EXAMPLES_BUILD_DIR -----"
cmake -S $EXAMPLES_DIR -B $EXAMPLES_BUILD_DIR -DCMAKE_BUILD_TYPE=$BUILD_TYPE
echo "----- Comlint examples' CMake configuration done -----"

echo "----- Building Comlint examples in $EXAMPLES_BUILD_DIR -----"
cmake --build $EXAMPLES_BUILD_DIR --config $BUILD_TYPE
echo "----- Comlint examples' build done -----"

echo "----- Installing comlint examples in $EXAMPLES_BUILD_DIR -----"
cmake --install $EXAMPLES_BUILD_DIR --config $BUILD_TYPE
echo "----- Comlint examples' installation done -----"