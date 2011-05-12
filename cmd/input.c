#include "precomp.h"
#include "cmd.h"
#include "input.h"
HANDLE hEvent;
HANDLE hKeyboard = NULL;
ULONG CurrentChar = 0;

CHAR InputBuffer[CMDLINE_LENGTH];
CHAR CurrentPosition = 0;

NTSTATUS InitInputDevice(VOID)
{
  UNICODE_STRING Driver;
  OBJECT_ATTRIBUTES ObjectAttributes;
  IO_STATUS_BLOCK Iosb;
  HANDLE hDriver;
  NTSTATUS Status;

  RtlInitUnicodeString(&Driver, L"\\Device\\KeyboardClass0");

  InitializeObjectAttributes(&ObjectAttributes,
                             &Driver,
                             OBJ_CASE_INSENSITIVE,
                             NULL,
                             NULL);

  Status = NtCreateFile(&hDriver,
                        SYNCHRONIZE | GENERIC_READ | FILE_READ_ATTRIBUTES,
                        &ObjectAttributes,
                        &Iosb,
                        NULL,
                        FILE_ATTRIBUTE_NORMAL,
                        0,
                        FILE_OPEN,
                        FILE_DIRECTORY_FILE,
                        NULL,
                        0);

  InitializeObjectAttributes(&ObjectAttributes, NULL, 0, NULL, NULL);
  Status = NtCreateEvent(&hEvent, EVENT_ALL_ACCESS, &ObjectAttributes, 1, 0);

  hKeyboard = hDriver;
  return Status;
}

NTSTATUS WaitForInput(IN HANDLE hDriver,
                      IN PVOID Buffer,
                      IN OUT PULONG BufferSize)
{
  IO_STATUS_BLOCK Iosb;
  LARGE_INTEGER ByteOffset;
  NTSTATUS Status;

  RtlZeroMemory(&Iosb, sizeof(Iosb));
  RtlZeroMemory(&ByteOffset, sizeof(ByteOffset));

  Status = NtReadFile(hDriver,
                      hEvent,
                      NULL,
                      NULL,
                      &Iosb,
                      Buffer,
                      *BufferSize,
                      &ByteOffset,
                      NULL);

  if (Status == STATUS_PENDING)
    {
      Status = NtWaitForSingleObject(hEvent, TRUE, NULL);
    }

  *BufferSize = (ULONG)Iosb.Information;
  return Status;
}

CHAR GetChar(VOID)
{
  KEYBOARD_INPUT_DATA KeyboardData;
  KBD_RECORD kbd_rec;
  ULONG BufferLength = sizeof(KEYBOARD_INPUT_DATA);
  if(!hKeyboard)
    {
      InitInputDevice();
    }
  WaitForInput(hKeyboard, &KeyboardData, &BufferLength);

  IntTranslateKey(&KeyboardData, &kbd_rec);

  if (!kbd_rec.bKeyDown)
    {
      return (-1);
    }
  return kbd_rec.AsciiChar;
}

PCHAR GetLine(VOID)
{
  CHAR Char;
  BOOLEAN First = FALSE;

  while (TRUE)
    {
      Char = GetChar();
      if (Char == '\r')
        {
          InputBuffer[CurrentPosition] = ANSI_NULL;
          CurrentPosition = 0;
          return InputBuffer;
        }
      else if (Char == '\b')
        {
          if (CurrentPosition)
            {
              PutChar(Char);
              CurrentPosition--;
            }
          continue;
        }
      if (!Char || Char == -1) continue;
      InputBuffer[CurrentPosition] = Char;
      CurrentPosition++;
      PutChar(Char);
    }
}

