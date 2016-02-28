FROM debian:latest

RUN apt-get update
RUN apt-get install -y --force-yes \
 build-essential \
 valgrind \
 git \
 python \
 libncurses5-dev

