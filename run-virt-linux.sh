#!/bin/sh
set -o xtrace

timeout --foreground 15 \
  qemu-system-riscv64 -machine virt \
  -bios RISCVVIRT-FV/RISCVVIRT.fd \
  -drive file=rootfs.ext2,format=raw,id=hd0 \
  -device virtio-blk-device,drive=hd0 \
  -drive file=fat:rw:fs_esp,format=raw,media=disk,id=hd1 \
  -device virtio-blk-device,drive=hd1 \
  -netdev user,id=net0 \
  -device virtio-net-device,netdev=net0 \
  -m 1024 -nographic -smp cpus=1,maxcpus=1 | tee boot.log \
  || true

grep -q 'Shell>' boot.log
grep -q 'Welcome to Buildroot' boot.log
# TODO: Figure out how to log in
