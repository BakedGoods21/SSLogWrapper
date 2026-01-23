#!/bin/bash
#ROOT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
ROOT_DIR=.
BUILD_FOLDER=$ROOT_DIR/build
INSTALL_FOLDER=$BUILD_FOLDER/install

VERBOSE=FALSE
MY_CONFIG=Release
CUSTOM_PREFIX=
ADDITIONAL_FLAGS=()
while [[ $# -gt 0 ]]; do
    case "$1" in
        -v|--verbose)
            VERBOSE=TRUE
            shift # Consume Argument
        ;;
        -c|--config)
            shift # Consume Argument
            MY_CONFIG="$1"
            shift # Consume Argument
        ;;
        -p|--cmake-prefix)
            shift # Consume Argument
            CUSTOM_PREFIX="$1"
            shift # Consume Argument
        ;;
            -d|--debug)
            shift # Consume Argument
            MY_CONFIG=Debug
        ;;
        *)
            ADDITIONAL_FLAGS+=("$1")
            shift # Consume Argument
        ;;
    esac
done

if [[ ! -z $CUSTOM_PREFIX ]]; then
    echo "Setting CMake Prefix: ${CUSTOM_PREFIX}"
    CUSTOM_PREFIX="-DCMAKE_PREFIX_PATH=$CUSTOM_PREFIX"
fi

(set -x; cmake -S $ROOT_DIR -B $BUILD_FOLDER -DCMAKE_BUILD_TYPE=$MY_CONFIG $CUSTOM_PREFIX -DCMAKE_INSTALL_PREFIX=${INSTALL_FOLDER} ${ADDITIONAL_FLAGS[@]})

