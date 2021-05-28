## @file
#  Definitions of Flash definition file on RiscvVirt RISC-V platform
#
#  Copyright (c) 2019, Hewlett Packard Enterprise Development LP. All rights reserved.<BR>
#
#  SPDX-License-Identifier: BSD-2-Clause-Patent
#
##
[Defines]
DEFINE BLOCK_SIZE        = 0x1000

DEFINE FW_BASE_ADDRESS   = 0x80000000
DEFINE FW_SIZE           = 0x00220000 # $(FW_BLOCKS) * 0x1000
DEFINE FW_BLOCKS         = 0x220      # $(CODE_BLOCKS) + $(VARS_BLOCKS)

#
# 0x000000-0x7DFFFF code
# 0x7E0000-0x800000 variables
#
DEFINE CODE_BASE_ADDRESS = 0x80000000 # $(FW_BASE_ADDRESS)
DEFINE CODE_SIZE         = 0x00200000 # $(CODE_BLOCKS) * 0x1000
DEFINE CODE_BLOCKS       = 0x020      # FV_MAIN_OFFSET + FV_MAIN_SIZE
DEFINE VARS_BLOCKS       = 0x20       # $(VARS_SIZE) / 0x1000

DEFINE SECFV_OFFSET      = 0x00000000
DEFINE SECFV_SIZE        = 0x00030000
DEFINE PEIFV_OFFSET      = 0x00030000
DEFINE PEIFV_SIZE        = 0x00080000
DEFINE SCRATCH_OFFSET    = 0x000b0000
DEFINE SCRATCH_SIZE      = 0x00010000
DEFINE FVMAIN_OFFSET     = 0x00100000 # Must be power of 2 for PMP setting
DEFINE FVMAIN_SIZE       = 0x00100000
DEFINE VARS_OFFSET       = 0x00200000 # $(CODE_SIZE)
DEFINE VARS_SIZE_0       = 0x00007000
DEFINE VARS_OFFSET_1     = 0x00207000 # $(VARS_OFFSET) + $(VARS_SIZE_0)
DEFINE VARS_SIZE_1       = 0x00001000
DEFINE VARS_OFFSET_2     = 0x00208000 # $(VARS_OFFSET_1) + $(VARS_SIZE_1)
DEFINE VARS_SIZE_2       = 0x00018000
DEFINE VARS_SIZE         = 0x00020000 # $(VARS_SIZE_0) + $(VARS_SIZE_1) + $(VARS_SIZE_2)

SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdVariableFdBaseAddress = $(FW_BASE_ADDRESS) + $(VARS_OFFSET)
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdVariableFdSize        = $(VARS_SIZE)
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdVariableFdBlockSize   = $(BLOCK_SIZE)

SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdFwStartAddress   = $(CODE_BASE_ADDRESS)
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdFwEndAddress     = $(CODE_BASE_ADDRESS) + $(SECFV_SIZE) + $(PEIFV_SIZE) + $(SCRATCH_SIZE)
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdOpenSbiStackSize = 8192
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdScratchRamBase   = $(CODE_BASE_ADDRESS) + $(SCRATCH_OFFSET)
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdScratchRamSize   = $(SCRATCH_SIZE)
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdTemporaryRamBase = $(CODE_BASE_ADDRESS) + $(FW_SIZE)
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdTemporaryRamSize = 0x10000


SET gUefiRiscVPkgTokenSpaceGuid.PcdRiscVMachineTimerFrequencyInHerz    = 1000000
# TODO: This can be dynamically configured in QEMU
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdHartCount                   = 1          # Total cores on U540 platform
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdBootHartId                  = 0          # Boot hart ID
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdBootableHartNumber          = 1          # The bootable hart core number.
                                                                                    # Which is incorporate with OpenSBI
                                                                                    # platform hart_index2id value.
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdPeiCorePrivilegeMode        = 1          # Set PeiCore to S-Mode
