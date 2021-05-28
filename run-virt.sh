#!/bin/sh
set -o xtrace

timeout --foreground 10 \
  qemu-system-riscv64 -machine virt \
  -bios RISCVVIRT-FV/RISCVVIRT.fd \
  -m 1024 -nographic -smp cpus=1,maxcpus=1 | tee boot.log \
  || true

grep -q 'Shell>' boot.log
