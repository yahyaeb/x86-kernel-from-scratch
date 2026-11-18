#!/bin/bash
set -e

docker run --rm -v "$PWD":/kfs -w /kfs ubuntu:22.04 bash -c \
  "apt-get update && apt-get install -y nasm gcc gcc-multilib make grub-pc-bin grub-common xorriso mtools && make && cp kernel.bin iso/boot/ && grub-mkrescue -o kfs.iso iso"

qemu-system-i386 -cdrom kfs.iso