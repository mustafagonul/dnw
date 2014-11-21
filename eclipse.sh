#!/bin/bash

mkdir ../dnw_debug
cd ../dnw_debug 
cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_ECLIPSE_VERSION=4.4 -DCMAKE_CXX_COMPILER_ARG1=-std=c++14 -DCMAKE_BUILD_TYPE=Debug  ../dnw
