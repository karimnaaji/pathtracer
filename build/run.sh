#!/bin/bash
# ./run.sh scene_name samples_per_pixel
# compile, build and run the path tracer
# stores the output inside images/

cmake .. && make

if [[ $? == 0 ]] 
then
    d1=$(date +"%s")

    ./pathtracer.out scenes/$1 $2
    
    if [[ $? != 0 ]] 
    then
        echo -e "$(tput setaf 1)Bash: An error occured while running ./pathtracer"
        exit $?
    fi

    d2=$(date +"%s")
    d=$(($d2-$d1))
    
    echo -e "$(tput bold)Bash: $(($d/60)) minutes and $(($d%60)) seconds elapsed."

    now=`date +"%d%b%Y-%s"`
    scene=`echo $1 | cut -d'.' -f1`
    filename="images/$scene-$now-$2sppx.png"
    
    mkdir -p images
    convert image.ppm $filename

    echo -e "$(tput bold)Bash: Image saved as $filename"
    if [[ "$OSTYPE" == "linux-gnu" ]]; then
        xdg-open $filename
    elif [[ "$OSTYPE" == "darwin12" ]]; then
        open $filename
    fi
    
    echo -e "$(tput bold)Bash: Remove of output file image.ppm"
    rm image.ppm
fi
