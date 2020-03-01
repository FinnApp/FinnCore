FROM ubuntu:bionic
MAINTAINER Maxim Ivanov <maxim11853@gmail.com>

RUN DEBIAN_FRONTEND=noninteractive apt-get update && apt-get install -y apt-transport-https ca-certificates gnupg software-properties-common wget curl
RUN DEBIAN_FRONTEND=noninteractive add-apt-repository ppa:ubuntu-toolchain-r/test && apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get update && apt-get install -y g++-8

RUN DEBIAN_FRONTED=noninteractive wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | apt-key add - && \
  apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main' && \
  apt-get update && \
  apt-get install -y cmake

RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-8 90
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 90

ENV GTEST=1.8.1
RUN curl -o /root/gtest.tar.gz https://codeload.github.com/google/googletest/tar.gz/release-${GTEST} && \
    cd /root && \
    tar -zxvf gtest.tar.gz && \
    cd googletest-release-${GTEST} && \
    cmake . && \
    make -j4 && \
    make install && \
    cd /root && \
    rm -r googletest-release-${GTEST} && \
    rm gtest.tar.gz

CMD ["/bin/bash"]