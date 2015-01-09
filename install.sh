#!/bin/bash


# get this file with 
#
# wget https://raw.githubusercontent.com/mustafagonul/dnw/master/install.sh
#
# and run it :)

git clone https://github.com/mustafagonul/dnw.git

mkdir dnw_release
cd dnw_release/
cmake -DCMAKE_BUILD_TYPE=Release ../dnw
make -j$(nproc)
make install

cd ..
rm -R dnw
rm -R dnw_release

