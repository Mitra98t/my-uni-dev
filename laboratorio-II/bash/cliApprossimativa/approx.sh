#!/bin/bash

reqCommand=""
reqParam=""

if echo $* | grep -e "-c" -q
then
    while getopts ":c:p" opt; do
        case $opt in
            c)
            echo "trovato c $OPTARG"
            reqCommand=$OPTARG
            ;;
            p)
            echo "trovato p $OPTARG"
            reqParam=$4
            ;;
            \?)
            echo "Invalid option 1: -$OPTARG" >&2
            exit 1
            ;;
            :)
            echo "Option -$OPTARG requires an argument." >&2
            exit 1
            ;;
        esac
    done
else
  echo "NO -a"
  exit 1
fi


echo "$reqCommand"
echo "$reqParam"

a1=(ls ll)
a2=(cd mkdir)
