#!/bin/bash
export GCC5_RISCV64_PREFIX=riscv64-linux-gnu-
export PACKAGES_PATH=/edk2:/edk2-platforms
export EDK_TOOLS_PATH=/edk2/BaseTools

source /edk2/edksetup.sh
make -C edk2/BaseTools clean
make -C edk2/BaseTools
make -C edk2/BaseTools/Source/C

source edk2/edksetup.sh BaseTools

cd /edk2-platforms
build -a RISCV64 -p $1 -t GCC5 \
  && echo 'Completed EDK2 build' \
  || echo 'Failed EDK2 build'

#build -a RISCV64 -p MdeModulePkg/MdeModulePkg.dsc -t GCC5
#build -a RISCV64 -p CryptoPkg/CryptoPkg.dsc -t GCC5
#build -a RISCV64 -p MdePkg/MdePkg.dsc -t GCC5
#build -a RISCV64 -p OvmfPkg/OvmfPkgRISCV64.dsc -t GCC5
#build -a RISCV64 -p RiscVPkg/RiscVPkg.dsc -t GCC5
