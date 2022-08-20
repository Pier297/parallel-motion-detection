FROM ubuntu

# Set timezone to fix the tzdata issue
ENV TZ=Europe/Rome
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt update
RUN apt install -y libopencv-dev
RUN apt install -y build-essential
RUN apt install -y cmake
RUN apt install -y htop