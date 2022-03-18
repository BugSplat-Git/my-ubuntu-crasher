FROM ubuntu:21.10
ENV DEBIAN_FRONTEND=noninteractive
RUN apt update -y
RUN apt install -y git python llvm clang
ENV HOME=/home/foo
RUN mkdir -p $HOME/Desktop/github/my-ubuntu-crasher
COPY . $HOME/Desktop/github/my-ubuntu-crasher
WORKDIR $HOME/Desktop/github/my-ubuntu-crasher/scripts
RUN ./build.sh
