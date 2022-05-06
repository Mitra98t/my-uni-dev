if [ $# = 2 ] ; then
    if [ -d $1 ] ; then
        cd $1
        for file in * ; do
            if grep $2 $file &> /dev/null ; then
                echo $file
            fi
        done
    else
        echo "una dir"
    fi
else
    echo "mancano parametri"
fi
