//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Processos.h"
#include "winuser.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
ProcessStruct ProcessInfoArray[300];
int ProcessCount;
//---------------------------------------------------------------------------
bool EnumerateProcess( void ) {

  typedef DWORD (WINAPI *PEnumProcesses)( DWORD*, UINT, DWORD* );
  typedef DWORD (WINAPI *PEnumProcessModules)( HANDLE, HMODULE*, UINT, DWORD* );
  typedef DWORD (WINAPI *PGetModuleBaseName)( HANDLE, HMODULE, LPTSTR, UINT );

  HINSTANCE hPsApi;
  HANDLE hProcess;
  HMODULE hMod;
  _TCHAR szProcessName[MAX_PATH] = _T("unknown");
  DWORD processID[1024], cbNeeded, cProcesses;
  int i;

  hPsApi = LoadLibrary( _T("PSAPI.DLL") );

  if( hPsApi == NULL ) {
    return( false );
  }

  PEnumProcessModules EnumProcessModules = (PEnumProcessModules)GetProcAddress( hPsApi,
    "EnumProcessModules" );

#ifdef UNICODE
  PGetModuleBaseName GetModuleBaseName = (PGetModuleBaseName)GetProcAddress( hPsApi,
    "GetModuleBaseNameW" );
#else
  PGetModuleBaseName GetModuleBaseName = (PGetModuleBaseName)GetProcAddress( hPsApi,
    "GetModuleBaseNameA" );
#endif

  PEnumProcesses EnumProcesses = (PEnumProcesses)GetProcAddress( hPsApi,
    "EnumProcesses" );

  if( EnumProcessModules == NULL || GetModuleBaseName == NULL ||
      EnumProcesses == NULL ) {
    return( false );
  }
  // Get the list of process identifiers.
  if ( !EnumProcesses( processID, sizeof(processID), &cbNeeded ) ) {
    return( false );
  }
  // Calculate how many process identifiers were returned.
  cProcesses = cbNeeded / sizeof(DWORD);

  // Print the name and process identifier for each process.
  ProcessCount = 0;
  for( i = 0; i < (int)cProcesses; i++ ) {
    // Get a handle to the process.
    hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
      FALSE, processID[i] );

    if( hProcess ) {
      if( EnumProcessModules( hProcess, &hMod, sizeof(hMod), &cbNeeded) ) {
        GetModuleBaseName( hProcess, hMod, szProcessName, sizeof(szProcessName) );

        ProcessInfoArray[i].Name = szProcessName;
        ProcessInfoArray[i].Pid = processID[i];
        ProcessInfoArray[i].Handle = hProcess;
        EnumWindows( (WNDENUMPROC)EnumWindowsProc, (LPARAM)processID[i] );
      }
    }

    CloseHandle( hProcess );
    ProcessCount ++;
  }
  return( true );
}
//---------------------------------------------------------------------------
BOOL CALLBACK EnumWindowsProc( HWND hwnd, LPARAM lParam ) {

  DWORD dwPID;
  LONG dwStyle;

  GetWindowThreadProcessId( hwnd, &dwPID );
  if( dwPID == ProcessInfoArray[ProcessCount].Pid ) {
    //dwStyle = GetWindowLong( hwnd, GWL_EXSTYLE );
    //if( dwStyle && WS_EX_TOPMOST ) {
      ProcessInfoArray[ProcessCount].MainWindowHandle = hwnd;
      return( false );
    //}
  }
  return( true );
}
//---------------------------------------------------------------------------
HWND GetMainWindowHandle( String ApplicationName ) {

  int i;

  if( !EnumerateProcess( ) ) {
    return( NULL );
  }
  for( i = 0; i < ProcessCount; i++ ) {
    if( ProcessInfoArray[i].Name == ApplicationName ) {
      return( ProcessInfoArray[i].MainWindowHandle );
    }
  }
  return( NULL );
}
//---------------------------------------------------------------------------
DWORD GetProcessPid( String ApplicationName ) {

  int i;

  if( !EnumerateProcess( ) ) {
    return( NULL );
  }
  for( i = 0; i < ProcessCount; i++ ) {
    if( ProcessInfoArray[i].Name == ApplicationName ) {
      return( ProcessInfoArray[i].Pid );
    }
  }
  return( NULL );
}
//---------------------------------------------------------------------------
void CloseScreenSaver( void ) {

  if( GetProcessPid( "sstext3d.scr" ) != NULL ) {
    SendMessage( Application->Handle, WM_SYSCOMMAND, SC_SCREENSAVE, WM_CLOSE );
  }
}
//---------------------------------------------------------------------------
