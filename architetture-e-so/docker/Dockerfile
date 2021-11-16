## start from current
FROM ubuntu:groovy
MAINTAINER marcod
### install base programming tools
RUN apt update
RUN apt install -y vim nano gcc-arm-linux-gnueabihf qemu-user gdb-multiarch
### set up service ssh and net tools
RUN apt install -y ssh openssh-server net-tools
RUN service ssh start
### fix user
RUN useradd -ms /bin/bash aeso2021
### da rimettere a posto alla fine
USER aeso2021
WORKDIR /home/aeso2021
### Aliases
### build
RUN echo 'alias asmB="arm-linux-gnueabihf-gcc -static"' >> ~/.bashrc
### debug build
RUN echo 'alias asmD="arm-linux-gnueabihf-gcc -static -ggdb3"' >> ~/.bashrc
### debugrun bg
RUN echo 'debug () { qemu-arm -g "$2" "$1"; }' >> ~/.bashrc
### open gdb
RUN echo 'runDb () { gdb-multiarch -q --nh -ex "set architecture arm" -ex "file $1" -ex "target remote localhost:$2";}' >> ~/.bashrc
RUN echo '' >> ~/.bashrc
