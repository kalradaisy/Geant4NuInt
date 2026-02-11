
FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    wget \
    git \
    libxerces-c-dev \
    libexpat1-dev \
    libgl1-mesa-dev \
    libxmu-dev \
    libxi-dev \
    libmotif-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /opt

# Download Geant4
RUN wget https://gitlab.cern.ch/geant4/geant4/-/archive/v11.0.4/geant4-v11.0.4.tar.gz \
 && tar -xzf geant4-v11.0.4.tar.gz

# Build Geant4
RUN mkdir geant4-build && cd geant4-build && \
    cmake ../geant4-v11.0.4 \
      -DGEANT4_INSTALL_DATA=ON \
      -DGEANT4_USE_OPENGL_X11=OFF \
      -DGEANT4_USE_QT=OFF \
      -DGEANT4_BUILD_MULTITHREADED=ON \
      -DCMAKE_INSTALL_PREFIX=/opt/geant4-install \
 && make -j4 && make install

# Setup environment
ENV GEANT4_DIR=/opt/geant4-install
ENV PATH=/opt/geant4-install/bin:$PATH
ENV LD_LIBRARY_PATH=/opt/geant4-install/lib:$LD_LIBRARY_PATH

WORKDIR /workspace

