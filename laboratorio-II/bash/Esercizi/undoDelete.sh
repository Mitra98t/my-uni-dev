if ! [ -d "BIN" ] ; then
  echo "missing bin folder"
  exit 1
fi

lastPWD=$PWD

for p ; do
    cd "BIN"
    if [ -f "$p.gz" ] ; then
        if gzip -d "$p.gz" ; then
            $(mv "$p" "$lastPWD")
        fi
    fi
done
cd "$lastPWD"
exit 0
