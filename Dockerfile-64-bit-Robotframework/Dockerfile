FROM ubuntu:14.04

MAINTAINER Asif Sardar <engr.asif.sardar@gmail.com>

RUN dpkg --add-architecture i386

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && apt-get install -y \
	build-essential \
	gcc-multilib \
	gcc-4.8-multilib \
	g++-multilib \
	g++-4.8-multilib \
	#ia32-libs \
	#ia32-libs-multiarch \
	libc6-dev \
	libgmp-dev \
	libmpfr-dev \
	libmpc-dev \

	# Dependencies for python source code compilation
	zlib1g-dev \
	lib32z1-dev \
	libreadline-dev \
	libreadline6-dev \
	lib32readline-dev \
	lib32readline6-dev \
	libgdm-dev \
	libsqlite3-dev \
	libgdbm-dev \
	libdbm-ocaml-dev \
	libdb4o-cil-dev \
	libx11-dev \
	lib32bz2-dev \
	libbz2-dev \
	libncurses5-dev \
	lib32ncurses5-dev \
	tk-dev \
	git

ADD https://www.python.org/ftp/python/2.7.8/Python-2.7.8.tgz /home/Downloads/
WORKDIR /home/Downloads/
RUN tar zxvf Python-2.7.8.tgz
WORKDIR /home/Downloads/Python-2.7.8/
RUN BASECFLAGS=-m32 LDFLAGS=-m32 CFLAGS=-m32 ./configure --prefix=/opt/pym32
RUN make
RUN make install

ADD https://pypi.python.org/packages/source/r/robotframework/robotframework-2.8.7.tar.gz#md5=42a38054fb24787e6d767e0a96315627 /home/Downloads/
WORKDIR /home/Downloads/
RUN tar zxvf robotframework-2.8.7.tar.gz
WORKDIR /home/Downloads/robotframework-2.8.7
RUN /opt/pym32/bin/python setup.py install

ADD https://pypi.python.org/packages/source/d/docutils/docutils-0.12.tar.gz#md5=4622263b62c5c771c03502afa3157768 /home/Downloads/
WORKDIR /home/Downloads/
RUN tar zxvf docutils-0.12.tar.gz
WORKDIR /home/Downloads/docutils-0.12
RUN /opt/pym32/bin/python setup.py install

RUN git clone https://github.com/asifsardar26/Runtime.git /home/Runtime
RUN git --git-dir /home/Runtime/.git --work-tree /home/Runtime checkout feature-encX24J600-wip

RUN git clone https://github.com/asifsardar26/ELL-i-PyBot-Tests /home/Runtime/robot_tests/

RUN git clone git://github.com/RIOT-OS/RIOT /home/RIOT

VOLUME ["/home"]

WORKDIR /home

CMD ["/bin/bash"]
