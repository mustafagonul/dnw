#!/bin/bash

cd ..
spawn-fcgi -n -f ./dnw -a 0.0.0.0 -p 9091 > /dev/null 2>&1 &
