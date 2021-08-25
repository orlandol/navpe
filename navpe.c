
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

HANDLE systemConsoleBuffer = INVALID_HANDLE_VALUE;

Console* InitConsoleInterface() {
  Console* newConsole = NULL;

  newConsole = calloc(1, sizeof(Console));
  if( newConsole == NULL ) { return NULL; }

  stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  stdinHandle = GetStdHandle(STD_INPUT_HANDLE);

  if( stdoutHandle == INVALID_HANDLE_VALUE ) { goto ErrorExit; }
  if( stdinHandle == INVALID_HANDLE_VALUE ) { goto ErrorExit; }

  return NULL;

ErrorExit:
  FreeConsoleInterface( &newConsole );
  return NULL;
}

void FreeConsoleInterface( Console** consoleVar ) {
  stdoutHandle = INVALID_HANDLE_VALUE;
  stdinHandle = INVALID_HANDLE_VALUE;

  if( consoleVar ) {
    if( (*consoleVar) ) {
    }
    free( (*consoleVar) );
    (*consoleVar) = NULL;
  }
}

/*
 *  Main program
 */

Console* display = NULL;

void Cleanup() {
  FreeConsoleInterface( &display );
}

int main( int argc, char* argv[] ) {
  atexit( Cleanup );

  display = InitConsoleInterface();

  FreeConsoleInterface( &display );

  return 0;
}
