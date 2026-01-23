#!/bin/bash
#ROOT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
ROOT_DIR=.
BUILD_FOLDER=$ROOT_DIR/build

BUILD_JOBS=1
MY_CONFIG=Release
ADDITIONAL_FLAGS=()
while [[ $# -gt 0 ]]; do
    key=$1
    case $key in
        -j|--parallel)
        shift # Consume Argument
        BUILD_JOBS="$1"
        shift # Consome Argument
        ;;
        *)
        ADDITIONAL_FLAGS+=("$1")
        shift # Consume Argument
        ;;
    esac
done

mkdir -p $BUILD_FOLDER

(set -x; cmake --build $BUILD_FOLDER --config $MY_CONFIG --parallel $BUILD_JOBS ${ADDITIONAL_FLAGS[@]})

