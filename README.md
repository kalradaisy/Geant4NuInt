# Geant4MuC

## Geant4 Neutrino Simulation with Docker
This repository provides a Docker-based environment for building and running
a Geant4 neutrino simulation example. The setup ensures reproducibility and
avoids local dependency issues.

## ToDos

See the issues on this repo on GitHub for tasks.

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


## Docker Images

Images are available at https://github.com/kalradaisy/Geant4MuC/pkgs/container/geant4muc with Geant4 built with GDML and ROOT support. This tool is precompiled in these images, which are built, tested, and deployed automatically in GitHub actions.

### Building Geant4 manually

If you need to rebuild Geant4 in a fresh image, you can see the `DOCKERFILE` in this repository.

## Building the Neutrino Demo

```
mkdir build
cd build
cmake ../neutrino_demo
cmake --build . 
```

## Running the Simulation

```
./neutrino ../run.mac
```

## Installing optional tools

```
apt update -y
apt install -y emacs libxerces-c-dev
```
