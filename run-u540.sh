#!/bin/sh
set -o xtrace

timeout --foreground 10 \
  qemu-system-riscv64 \
  -cpu sifive-u54 -machine sifive_u \
  -bios U540-FV/U540.fd \
  -m 1024 -nographic -smp cpus=5,maxcpus=5 | tee boot.log \
  || true

grep -q 'Shell>' boot.log
