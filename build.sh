#!/bin/bash

git clone https://github.com/mustafagonul/dnw.git
mkdir dnw_release
cd dnw_release/
cmake -DCMAKE_BUILD_TYPE=Release ../dnw
make -j
