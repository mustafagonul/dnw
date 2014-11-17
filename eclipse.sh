#!/bin/bash

mkdir ../dnw_debug
cd ../dnw_debug
cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug ../dnw
