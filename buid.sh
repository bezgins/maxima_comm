#!/bin/bash

if [ ! -d "bin" ]
then
    echo -n "creating bin directory";
    mkdir bin;
fi

cd bin

cmake ./..
make

cd ..
