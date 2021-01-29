
#include <ctype.h>
#include <stdio.h>
#include <string.h>

  typedef enum Commands {
    quitNavpe = 1
  } Commands;

  size_t ReadCommandLine( char* destString, size_t destMaxLen );
  unsigned ParseCommandLine( char* sourceString, size_t sourceMaxLen );

  size_t ReadCommandLine( char* destString, size_t destMaxLen ) {
    size_t destIndex = 0;
    int inChar = '\0';

    if( !(destString && destMaxLen) ) {
      return 0;
    }

    printf( "navpe> " );

    while( inChar != EOF ) {
      inChar = getchar();

      if( inChar == '\n' ) {
        break;
      }

      if( isprint(inChar) && ((destIndex + 1) < destMaxLen) ) {
        destString[destIndex++] = (char)inChar;
      }
    }
    destString[destIndex] = '\0';

    return destIndex;
  }

  unsigned ParseCommandLine( char* sourceString, size_t sourceMaxLen ) {
    if( !(sourceString && sourceMaxLen) ) {
      return 0;
    }

    if( strncmp(sourceString, "quit", sourceMaxLen) == 0 ) {
      return quitNavpe;
    }

    return 0;
  }

int main( int argc, char* argv[] ) {
  char navpeCommandLine[1024] = {};
  size_t cmdLen;
  unsigned command;

  fflush( stdin );

  do {
    cmdLen = ReadCommandLine(navpeCommandLine, sizeof(navpeCommandLine) - 1);

    command = ParseCommandLine(navpeCommandLine, cmdLen);
  } while( command != quitNavpe );

  return 0;
}
