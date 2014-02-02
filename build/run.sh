#!/bin/bash
make
if [[ $? == 0 ]] 
then
    ./raytracer.out
    convert image.ppm image.png
    open image.png
fi
