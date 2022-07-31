#!/bin/sh
set -e

DIRS=("./")

for DIR in "${DIRS[@]}"
do
    find $DIR -iname "*.hpp" -o -iname "*.cpp" -o -iname "*.h"  | xargs clang-format -i
done
