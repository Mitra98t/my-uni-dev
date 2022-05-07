if [ $# -gt 0 ] ; then
    if ! [ -d "BIN" ] ; then
        mkdir "BIN" &> /dev/null
    fi
    for p ; do
        if [ -f $p ] ; then
            if gzip -f $p ;then
                $(mv "$p.gz" "BIN")
            fi
        fi
    done
else
    echo "mancano argomenti"
fi
