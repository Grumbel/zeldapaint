#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <allegro.h>

// Pseudo-Funktionen
#define frand() (float)rand()/RAND_MAX
#define rnd(a) (int)(frand()*a)
#define fit16x(a) ((a/16)*16)
#define fit16y(a) (((a-16)/16)*16+16)
#define fit16(a) ((a/16)*16)
#define KILL_STATUS_LINE rectfill(screen, 17, 0, 319, 20,0);
#define exist(a) !access(a,00)

// Konstanten
#define maxSprite 60
#define minSprite 0
#define ESC 27

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
