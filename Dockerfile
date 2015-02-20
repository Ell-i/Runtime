FROM 32bit/ubuntu:14.04

MAINTAINER Asif Sardar <engr.asif.sardar@gmail.com>

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && apt-get install -y \
	make \
	gcc \
	g++ \
	git \
	python2.7 \
	python2.7-dev \
	python-setuptools \
	wget \
	zip \
	unzip \
	bridge-utils \
	valgrind \
	nano

ADD https://launchpad.net/gcc-arm-embedded/4.9/4.9-2014-q4-major/+download/gcc-arm-none-eabi-4_9-2014q4-20141203-linux.tar.bz2 /home/Downloads/
WORKDIR /home/Downloads/
RUN tar xvjf gcc-arm-none-eabi-4_9-2014q4-20141203-linux.tar.bz2

ENV PATH /home/Downloads/gcc-arm-none-eabi-4_9-2014q4/bin:$PATH

RUN easy_install -Z robotframework
RUN easy_install -Z docutils

RUN git clone https://github.com/asifsardar26/Runtime.git /home/Runtime
RUN git --git-dir /home/Runtime/.git --work-tree /home/Runtime checkout feature-encX24J600-wip

RUN git clone https://github.com/asifsardar26/ELL-i-PyBot-Tests /home/Runtime/robot_tests/

RUN git clone git://github.com/RIOT-OS/RIOT /home

#WORKDIR /home/Runtime/stm32/tests/robot_library/
#RUN make PLATFORM=emulator

VOLUME ["/home"]

WORKDIR /home/Runtime/robot_tests

USER elli

CMD ["/bin/bash"]
