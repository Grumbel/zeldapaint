// Copyright (c) 1997 Ingo Ruhnke <grumbel@gmail.com>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgement in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

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
