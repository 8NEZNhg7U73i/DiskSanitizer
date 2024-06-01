#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/SimpleTextInEx.h>

#include "DiskDevice.h"

typedef struct program_variables{
    /*Protocols*/
    EFI_DEVICE_PATH_TO_TEXT_PROTOCOL* devicePathToTextProtocol;
    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL* inputExProtocol;

    /*Variables*/
    disk_device diskDevices[8];
    UINTN diskDevicesCount;
    UINTN chosenDisk;
    UINTN exitProgram;

} program_variables;

typedef enum menu_options{
    SHOW_CURRENTLY_CHOSEN_DISK,
    CHOOSE_DISK,
    TEST_WRITE_CONTENT_TO_DISK,
    ERASE_DISK,
    READ_DISK,
    EXIT,
    NOT_EXIT,
} menu_options;

CHAR16 EFIAPI ReadKey(EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL* inputExProtocol);

EFI_STATUS InitializeProgramVariables(program_variables* programVariables);
EFI_STATUS EFIAPI RunTheProgram(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
EFI_STATUS DeinitializeProgramVariables(program_variables* programVariables);

EFI_STATUS EraseTheDrive(disk_device* diskDevice, UINT8 numberToWrite);
EFI_STATUS ShowDiskContent(disk_device* diskDevice);

void PrintAllDrives(disk_device* diskDevices, UINTN numHandles);
void PrintWelcomeMessage();
void PrintMenu();
