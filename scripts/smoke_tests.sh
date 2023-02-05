#!/bin/bash

SCRIPTS_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
REPO_DIR=$SCRIPTS_DIR/..
EXAMPLE_APPS_BIN_DIR=$REPO_DIR/examples/build/bin

echo "----- Running parsing example application -----"
LD_LIBRARY_PATH=$EXAMPLE_APPS_BIN_DIR $EXAMPLE_APPS_BIN_DIR/parsing_example_app
echo "----- Parsing example application done -----"

echo "----- Running running example application -----"
LD_LIBRARY_PATH=$EXAMPLE_APPS_BIN_DIR $EXAMPLE_APPS_BIN_DIR/running_example_app
echo "----- Running example application done -----"