#!/usr/bin/env bash

# This is a test script for devpkg

set -e

# create the database
echo Initializing the database
devpkg -S

# download higan/bsnes
echo Fetching Bsnes files
devpkg -F git://gitorious.org/bsnes/bsnes.git

# build higan/bsnes
echo Building Bsnes files
devpkg -B git://gitorious.org/bsnes/bsnes.git
