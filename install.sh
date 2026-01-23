#!/bin/bash
#ROOT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
ROOT_DIR=.
BUILD_FOLDER=$ROOT_DIR/build
INSTALL_FOLDER=$BUILD_FOLDER/install

CONFIG=Release
ADDITIONAL_FLAGS=$()
while [[ $# -gt 0 ]]; do
    key=$1
    case $key in
        -d|--debug)
        shift # Consume Argument
        CONFIG=Debug
        ;;
        -c|--config)
        shift # Consume Argument
        CONFIG="$1"
        shift # Consume Argument
        ;;
        *)
        ADDITIONAL_FLAGS+=("$1")
        shift # Consume Argument
        break;
        ;;
    esac
done

mkdir -p $BUILD_FOLDER
mkdir -p $INSTALL_FOLDER

(set -x; cmake --install $BUILD_FOLDER --config $CONFIG --prefix $INSTALL_FOLDER ${ADDITIONAL_FLAGS[@]})

