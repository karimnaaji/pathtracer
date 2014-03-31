#!/bin/bash
# must be ran into osx/ or linux/ folder inside build/
cmake ../..
make
if [[ $? == 0 ]] 
then
    d1=$(date +"%s")
    ./raytracer.out scenes/$1 $2
    d2=$(date +"%s")
    d=$(($d2-$d1))
    echo "$(($d/60)) minutes and $(($d%60)) seconds elapsed."

    now=`date +"%d%b%Y-%s"`
    scene=`echo $1 | cut -d'.' -f1`
    filename="../images/$scene-$now-$2sppx.png"
    convert image.ppm $filename

    echo "filename: $filename"
    if [[ "$OSTYPE" == "linux-gnu" ]]; then
        xdg-open $filename
    elif [[ "$OSTYPE" == "darwin12" ]]; then
        open $filename
    fi
    rm -v image.ppm
fi
