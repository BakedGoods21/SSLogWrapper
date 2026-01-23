#!/bin/bash
#ROOT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
ROOT_DIR=.
BUILD_FOLDER=$ROOT_DIR/build
 
pushd $BUILD_FOLDER
(set -x; ctest $BUILD_FOLDER $@)
popd

