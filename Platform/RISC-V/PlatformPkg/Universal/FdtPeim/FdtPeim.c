/** @file
The module to pass the device tree to DXE via HOB.

Copyright (c) 2021, Hewlett Packard Enterprise Development LP. All rights reserved.<BR>

SPDX-License-Identifier: BSD-2-Clause-Patent

**/

//#include <PiPei.h>
//
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
//#include <Library/PcdLib.h>
//#include <Library/PeiServicesLib.h>
#include <libfdt.h>
#include <Guid/FdtHob.h>


/**
  The entrypoint of the module, it will pass the FDT via a HOB.

  @param  FileHandle             Handle of the file being invoked.
  @param  PeiServices            Describes the list of possible PEI Services.

  @retval TODO
**/
EFI_STATUS
EFIAPI
PeimPassFdt (
  IN EFI_PEI_FILE_HANDLE        FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  UINTN  *FdtPointer;
  VOID   *Base;
  VOID   *NewBase;
  UINTN  FdtSize;
  UINTN  FdtPages;
  UINT64 *FdtHobData;

  // We can either get it from here or from the ScratcSpace
  FdtPointer = (VOID*)(UINTN)PcdGet64 (PcdDeviceTreeInitialBaseAddress);

  Base = (VOID *)*FdtPointer;
  ASSERT (Base != NULL);
  ASSERT (fdt_check_header (Base) == 0);

  FdtSize = fdt_totalsize (Base) + 256;//PcdGet32 (PcdDeviceTreeAllocationPadding);
  FdtPages = EFI_SIZE_TO_PAGES (FdtSize);
  NewBase = AllocatePages (FdtPages);
  ASSERT (NewBase != NULL);
  fdt_open_into (Base, NewBase, EFI_PAGES_TO_SIZE (FdtPages));

  FdtHobData = BuildGuidHob (&gFdtHobGuid, sizeof *FdtHobData);
  ASSERT (FdtHobData != NULL);
  *FdtHobData = (UINTN)NewBase;

  return EFI_SUCCESS;
}
