#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <allegro.h>
#include "header.h"

void save_map(char *filename, int map[10][8])
{
  FILE *out;
  int x,y;

  if ((out = fopen(filename, "wb")) != NULL) {
    for (y=0; y<8; ++y)
      for(x=0; x<10; ++x) {
	fputc(map[x][y], out);
      }
    fclose(out);
  }
}

void load_map(char *filename, int map[10][8])
{
  FILE *out;
  int x,y;

  if ((out = fopen(filename, "rb")) != NULL) {
    for (y=0; y<8; ++y)
      for(x=0; x<10; ++x) {
	map[x][y] = fgetc(out);
      }
    
  }
}

void getstring(char *dateiname)
{
  int i;
  char c=0;

  rect(screen, 49, 0, 146, 9, 150);

  for (i=0; c != '\r' && c != '\n'; ++i) {  
    c = readkey();

    if (c == '\b') {
      --i;
      dateiname[i] = ' ';
      textout(screen, font, dateiname, 50, 1, 255);
      --i;
      if (i < -1)
	i = -1;
      continue;
    } else if (!isgraph(c)){
      --i;
      continue; 
    }

    if (i > 11)
      i = 11;

    dateiname[i] = c;
    dateiname[i+1] = '\0';
    textout(screen, font, dateiname, 50, 1, 255);
  }
  dateiname[i] = '\0';
  KILL_STATUS_LINE;
}
