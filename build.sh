#!/bin/bash

if [ ! -d "bin" ]
then
    echo -n "creating bin directory";
    mkdir bin;
fi

slice2cpp --output-dir slice slice/Maxima.ice 

cd bin

cmake ./.. && make

cd ..
