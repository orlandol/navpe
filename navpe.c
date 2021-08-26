
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h>

/*
 *  Console UI declarations
 */

typedef struct Console {
  HANDLE buffer;
} Console;

Console* CreateConsoleInterface();
void FreeConsoleInterface( Console** consoleVar );

/*
 *  Console UI implementation
 */
HANDLE stdoutHandle = INVALID_HANDLE_VALUE;
HANDLE stdinHandle = INVALID_HANDLE_VALUE;

// Begin system buffer implementation
// System buffer save/restore implementation
// - Save system console buffer and parameters
// - Change console parameters and run program
// - Restore system console buffer and parameters
//
CHAR_INFO* systemBuffer = NULL;
COORD systemDimensions = {};
COORD systemCursorPos = {};
// End system buffer implementation

Console* InitConsoleInterface() {
  Console* newConsole = NULL;

  newConsole = calloc(1, sizeof(Console));
  if( newConsole == NULL ) { return NULL; }

  stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  if( stdoutHandle == INVALID_HANDLE_VALUE ) { goto ErrorExit; }

  stdinHandle = GetStdHandle(STD_INPUT_HANDLE);
  if( stdinHandle == INVALID_HANDLE_VALUE ) { goto ErrorExit; }

  // Save system console buffer and parameters

  return NULL;

ErrorExit:
  stdoutHandle = INVALID_HANDLE_VALUE;
  stdinHandle = INVALID_HANDLE_VALUE;

  FreeConsoleInterface( &newConsole );

  // Restore system console buffer and parameters

  return NULL;
}

void FreeConsoleInterface( Console** consoleVar ) {
  stdoutHandle = INVALID_HANDLE_VALUE;
  stdinHandle = INVALID_HANDLE_VALUE;

  if( consoleVar ) {
    if( (*consoleVar) ) {
      CloseHandle( (*consoleVar)->buffer );
      (*consoleVar)->buffer = NULL;
    }
    free( (*consoleVar) );
    (*consoleVar) = NULL;
  }
}

/*
 *  Main program
 */

Console* activeConsole = NULL;
Console* secondaryConsole = NULL;

void Cleanup() {
  FreeConsoleInterface( &activeConsole );

  // Restore system console buffer and parameters
}

int main( int argc, char* argv[] ) {
  atexit( Cleanup );

  activeConsole = InitConsoleInterface();

  FreeConsoleInterface( &activeConsole );

  return 0;
}
