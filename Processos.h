//---------------------------------------------------------------------------
#ifndef ProcessosH
#define ProcessosH
//---------------------------------------------------------------------------
#include <tchar.h>
//---------------------------------------------------------------------------
typedef struct Process {
  String Name;
  DWORD Pid;
  HWND Handle, MainWindowHandle;
} ProcessStruct;
//---------------------------------------------------------------------------
bool EnumerateProcess( void );
BOOL CALLBACK EnumWindowsProc( HWND hwnd, LPARAM lParam );
HWND GetMainWindowHandle( String ApplicationName );
DWORD GetProcessPid( String ApplicationName );
void CloseScreenSaver( void );
//---------------------------------------------------------------------------
#endif
