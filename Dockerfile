FROM ubuntu:latest

# Installation des outils nécessaires
RUN apt-get update && apt-get install -y \
    nasm \
    gcc \
    binutils \
    xorriso \
    mtools \
    grub-pc-bin \
    grub-common \
    make

# On définit le dossier de travail
WORKDIR /root/env

# Par défaut, on lance un bash
CMD ["/bin/bash"]