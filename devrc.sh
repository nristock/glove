#!/bin/bash
# source this file to set up a basic dev environment

SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do
  DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
  SOURCE="$(readlink "$SOURCE")"
  [[ $SOURCE != /* ]] && SOURCE="$DIR/$SOURCE"
done
DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"

export GLOVE_DEV_ROOT=$DIR
alias mocca="python3 $DIR/tools/mocca/mocca.py $@"
alias glodu="python3 $DIR/scripts/glodu.py $@"
