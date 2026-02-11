# Geant4MuC
# Geant4 Neutrino Simulation with Docker
This repository provides a Docker-based environment for building and running
a Geant4 neutrino simulation example. The setup ensures reproducibility and
avoids local dependency issues.

## Repository Structure

geant4-neutrino/
├── Dockerfile
├── neutrino_demo/
│ ├── src/
│ ├── include/
│ ├── CMakeLists.txt
│ └── run.mac
├── .gitignore
└── README.md

geant4-source and build directories are not included and are downloaded
inside the container.

## Building the Docker Image
docker build --platform linux/amd64 -t geant4-clean .
## Running the Container
docker run -it --rm -v "$PWD":/workspace geant4-clean bash
Inside the container, initialize Geant4:
source /opt/geant4-install/bin/geant4.sh
## Downloading Geant4 Source
Inside the container:
cd /workspace
git clone --branch v11.0.4 https://gitlab.cern.ch/geant4/geant4.git geant4-source
## Building Geant4
cd /workspace
mkdir build
cd build

cmake ../geant4-source \
  -DCMAKE_INSTALL_PREFIX=/opt/geant4-install \
  -DGEANT4_USE_GDML=ON \
  -DGEANT4_INSTALL_DATA=ON \
  -DGEANT4_USE_OPENGL_X11=ON \
  -DGEANT4_USE_QT=OFF

make -j4
make install

Reload environment:
source /opt/geant4-install/bin/geant4.sh

## Building the Neutrino Demo
cd /workspace/neutrino_demo
mkdir build
cd build

cmake ../
make -j4

## Running the Simulation
./neutrino ../run.mac

## Installing optional tools
apt update -y
apt install -y emacs libxerces-c-dev

