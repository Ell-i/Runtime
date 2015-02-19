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
	python-setuptools

RUN easy_install -Z robotframework
RUN easy_install -Z docutils

RUN git clone https://github.com/asifsardar26/Runtime.git /home/Runtime
RUN git --git-dir /home/Runtime/.git --work-tree /home/Runtime checkout feature-encX24J600-wip

RUN git clone https://github.com/Ell-i/ELL-i-PyBot-Tests.git /home/Runtime/robot_tests/

WORKDIR /home/Runtime/stm32/tests/robot_library/
RUN make PLATFORM=emulator

VOLUME ["/home"]

WORKDIR /home/Runtime/robot_tests

CMD ["/bin/bash"]
