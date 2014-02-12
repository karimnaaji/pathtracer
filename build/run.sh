#!/bin/bash
make
if [[ $? == 0 ]] 
then
    ./raytracer.out test.sc $1
    convert image.ppm image.png
    open image.png
fi
