typedef struct _KBD_RECORD {
  WORD  wVirtualScanCode;
  DWORD dwControlKeyState;
  UCHAR AsciiChar;
  BOOL  bKeyDown;
} KBD_RECORD, *PKBD_RECORD;

void IntTranslateKey(PKEYBOARD_INPUT_DATA InputData, KBD_RECORD *kbd_rec);