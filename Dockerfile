FROM debian:sid

# disable tzdata questions
ENV DEBIAN_FRONTEND=noninteractive

# use bash
SHELL ["/bin/bash", "-c"]

# install apt-utils
RUN apt-get update -y && \
  apt-get install -y apt-utils 2> >( grep -v 'debconf: delaying package configuration, since apt-utils is not installed' >&2 ) \
  && apt-get clean && rm -rf /var/lib/apt/lists/*

# essential tools
RUN apt-get update -y && apt-get install -y --no-install-recommends \
  ca-certificates \
  netbase \
  curl \
  git \
  gnupg \
  && apt-get clean && rm -rf /var/lib/apt/lists/*

# enable Intel MKL
RUN curl https://apt.repos.intel.com/intel-gpg-keys/GPG-PUB-KEY-INTEL-SW-PRODUCTS-2019.PUB -o /tmp/GPG-PUB-KEY-INTEL-SW-PRODUCTS-2019.PUB \
  && apt-key add /tmp/GPG-PUB-KEY-INTEL-SW-PRODUCTS-2019.PUB \
  && rm /tmp/GPG-PUB-KEY-INTEL-SW-PRODUCTS-2019.PUB \
  && echo "deb https://apt.repos.intel.com/mkl all main" > /etc/apt/sources.list.d/intel-mkl.list \
  && echo "deb https://apt.repos.intel.com/mpi all main" > /etc/apt/sources.list.d/intel-mpi.list

# install MKL
RUN apt-get update -y && apt-get install -y --no-install-recommends \
  build-essential \
  intel-mkl-2020.0-088

# copy files
COPY . /tmp/intel-mkl-examples
WORKDIR /tmp/intel-mkl-examples

# configure image for remote development
#RUN bash zscripts/common-debian.sh
