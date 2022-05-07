#!/bin/bash

isDir(){
    if [ ! -d $1 ]; then
        echo "$1 is not a directory"
        exit 1
    fi
}

isDirEmpty(){
    if [ -z "$(ls -A $1)" ]; then
        echo "$1 is empty"
        exit 1
    fi
}

getCurrDirSize(){
    filesSize=$( find $1 -type f -printf '%s\n' )
    currdim=0
    for size in $filesSize; do
        currdim=$(( $currdim + $size ))
    done
    echo $currdim
}

if [ ! $# -eq 8 ]; then
    echo "Missing arguments"
    exit 1
fi

while getopts d:s:f:n: flag
do
    case "${flag}" in
        d) dirname=${OPTARG};;
        s) size=${OPTARG};;
        f) warningFactor=${OPTARG};;
        n) maxnum=$(bc -l <<<"${OPTARG}");;
    esac
done

isDir $dirname 
isDirEmpty $dirname

currSizeString=$( getCurrDirSize $dirname )

echo "dimensione corrente occupata -> $currSizeString"

convertedSize=$(( $size*1024*1024 ))
remaining=$(bc -l <<<"${convertedSize}-${currSizeString}")
warningLevel=$(bc -l <<<"${convertedSize}*${warningFactor}")

if [ $maxnum -eq 0 ]; then
    maxnum=$( ls $dirname -1q | wc -l )
fi


i=0
while (( $(echo "$remaining < $warningLevel" | bc -l) && $(echo "$i < $maxnum" | bc -l) ))
do
    echo "spazio rimanente è minore dello spazio * warning factor quindi devo cancellare qualcosa"
    fileData=$(find $dirname -type f -printf '%A@ %s %p\n' | sort | head -n 1)
    fileToRemName=$( echo $fileData | cut -f3 -d " " )
    rm -f $fileToRemName
    echo "rimosso $fileToRemName"
    dimToRemove=$( echo $fileData | cut -f2 -d " " )
    remaining=$(( $remaining+$dimToRemove ))
    i=$(( $i + 1 ))
    echo "liberati $dimToRemove byte di spazio"
done
echo "rimossi sufficienti file per rendere lo spazio rimanente maggiore di spazio * warning factor"
exit 0

# dd if=/dev/zero of=file2 bs=1M count=3 && sleep 0.5 && dd if=/dev/zero of=file3 bs=1M count=5 && sleep 0.5 && dd if=/dev/zero of=file1 bs=1M count=5