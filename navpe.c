
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <conio.h>

#define KEY_BACKSPACE 8
#define KEY_CTRLENTER 10
#define KEY_ENTER 13
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DEL 83

/*
 *  Main program
 */

int main( int argc, char* argv[] ) {
  char commandLine[1024] = {};
  size_t commandLength = 0;
  size_t commandPos = 0;
  int ch;

  do {
    ch = _getch();

    switch( ch ) {
    case KEY_BACKSPACE:
      if( commandLength && commandPos ) {
        memmove( &commandLine[commandPos - 1],
          &commandLine[commandPos], commandLength - commandPos );
        commandLine[commandLength - 1] = '\0';
        commandPos--;
        commandLength--;
        putchar( 8 );
      }
      break;

    case KEY_ENTER:
      printf( "\n" );
      break;

    case 0:
    case 224:
      ch = _getch();
      switch( ch ) {
      case KEY_LEFT:
        if( commandPos ) {
          commandPos--;
        }
        putchar( 8 );
        break;

      case KEY_RIGHT:
        if( commandPos < commandLength ) { commandPos++; }
        break;

      case KEY_DEL:
        if( commandLength && commandPos ) {
          memmove( &commandLine[commandPos],
            &commandLine[commandPos + 1], commandLength - commandPos - 1 );
          commandLine[commandLength] = '\0';
          commandPos--;
          commandLength--;
          putchar(8);
        }
        break;
      }
      break;

    default:
      if( isprint(ch) ) {
        if( commandLength < sizeof(commandLine) ) {
          commandLine[commandPos] = ch;
          if( commandPos == commandLength ) { commandLength++; }
          commandPos++;
        }
        putchar( ch );
      }
    }
  } while( ch != KEY_ENTER  );

  printf( "[%s]\n", commandLine );

  return 0;
}
