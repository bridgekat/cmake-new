#!/bin/sh

# If the project directory structure looks like this:
#
# - project [current directory]
#   - .gitignore
#   - README.md
#   - LICENCE
#   - CMakeLists.txt
#   - ...
#   - extern/ [submodules directory]
#     - ...
#     - prelude/ [this repository]
#       - ...
#       - misc/
#         - ...
#         - init.sh
#
# Then use `./extern/prelude/misc/init.sh` to copy all files contained in `misc`
# folder to the project root directory.
#
# Warning: this will overwrite all existing files with the same name.

# Obtain script directory.
# See: https://stackoverflow.com/questions/4774054/reliable-way-for-a-bash-script-to-get-the-full-path-to-itself
SCRIPT_DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

# Copy all files.
cp -R $SCRIPT_DIR/. .
