FROM ubuntu:21.10
ENV DEBIAN_FRONTEND=noninteractive
RUN apt update -y
RUN apt install -y git python llvm clang

ENV HOME=/home/foo
ENV CRASHPAD_CHECKOUT_DIR=$HOME/Desktop/crashpad/crashpad
ENV CRASHPAD_BUILD_DIR=$CRASHPAD_CHECKOUT_DIR/out/Default
ENV PROJECT_DIR=$HOME/Desktop/github/my-ubuntu-crasher
ENV CRASHPAD_DIR=$PROJECT_DIR/crashpad
ENV OUT_DIR=$PROJECT_DIR/out
ENV MODULE_NAME=myUbuntuCrasher.out
ENV BUGSPLAT_DATABASE=fred
ENV BUGSPLAT_APP_NAME=myUbuntuCrasher
ENV BUGSPLAT_APP_VERSION=1.0.0

RUN mkdir -p $HOME/Desktop/github/my-ubuntu-crasher
COPY . $HOME/Desktop/github/my-ubuntu-crasher
WORKDIR $HOME/Desktop/github/my-ubuntu-crasher/scripts
RUN ./build.sh
CMD ${OUT_DIR}/${MODULE_NAME}
