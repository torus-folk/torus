# Usage: docker build .
# Usage: docker run tpruvot/cpuminer-multi -a xevan --url=stratum+tcp://yiimp.ccminer.org:3739 --user=iGadPnKrdpW3pcdVC3aA77Ku4anrzJyaLG --pass=x

FROM		ubuntu:16.04
MAINTAINER	cv <cv.swan20@gmail.com>
WORKDIR		/torus
RUN     echo "05-02-2020"
RUN		apt-get update
RUN		apt-get install -y build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils python3
RUN		apt-get install -y libboost-all-dev
RUN		apt-get install -y software-properties-common
RUN		add-apt-repository ppa:bitcoin/bitcoin
RUN		apt-get update
RUN		apt-get install -y libdb4.8-dev libdb4.8++-dev
ADD		. .
RUN     ./autogen.sh
RUN     ./configure
RUN     make -j 9
ENTRYPOINT	["./src/torusd"]