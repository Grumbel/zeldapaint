#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <allegro.h>

#include "header.h"

void load_map(char *filename, int map[10][8]);
void save_map(char *filename, int map[10][8]);

struct BITMAP*
load_bmp_with_check(const char* filename, struct RGB* pal)
{
  BITMAP* result = load_bmp(filename, pal);
  if (!result)
  {
    perror(filename);
    abort();
  }
  return result;
}

int main(int argc, char *argv[1])
{
  PALLETE my_pallete;
  int index;
  char repaint_status_line=0;
  BITMAP *sprite_bmp;
  BITMAP *save_bmp;
  char repaint_map=0;
  char exit_zeldapaint=0;
  char Sprite[maxSprite+1][30];
  char Pfad[14];
  char Datei[14];
  char buf[20];
  int map[10][8];
  char c;
  FILE *in;
  int x,y,i;

  // liest Sprite Namen aus Datei ein
  in = fopen("sprite.ini", "r");
  strcpy(Pfad, "Sprite/");
  for (index=0; index <= maxSprite; ++index) {
    fscanf(in, "%s", Datei);
    strcpy(Sprite[index], Pfad);
    strcat(Sprite[index], Datei);
  }
  fclose(in);

  for (x=0; x<10; ++x)
    for (y=0; y<8; ++y)
      map[x][y] = 0;
  allegro_init();
  install_keyboard();
  install_mouse();
  install_timer();

  if (argc == 2) {
    strcat(argv[1], ".map");
    if (!exist(argv[1])) {
      printf("Datei \"%s\" konnte nicht gefunden werden.", argv[1]);
      allegro_exit();
      return 1;
    }
    printf ("lade...\n");
    load_map(argv[1], map);
    printf ("Datei \"%s\" geladen\n", argv[1]);
    repaint_map = TRUE;
  }

  set_gfx_mode(GFX_AUTODETECT_WINDOWED, 320, 200, 0, 0);
  set_mouse_speed(2,2);
  set_mouse_range(80, 32, 239, 159);

  index = minSprite;
  sprite_bmp = load_bmp_with_check(Sprite[index], my_pallete);
  set_pallete (my_pallete);
  clear(screen);

  blit (sprite_bmp, screen, 0, 0, 0, 0, 16, 16);
  sprintf (buf, "%3d - %s", index, Sprite[index] + strlen(Pfad));
  status_line(buf);
  hline(screen, 0, 22, 319, 255);
  rect(screen, 79, 31, 240, 160,50);

  save_bmp = create_sub_bitmap(screen, 80, 32, 160, 128);

  show_mouse(screen);

  while (!exit_zeldapaint) {
    if (mouse_b & 1) {
      map[mouse_x/16-5][mouse_y/16-2] = index;
      show_mouse(0);
      blit (sprite_bmp, screen,
            0,0,
            fit16x(mouse_x), fit16y(mouse_y),
            16, 16
        );
      show_mouse(screen);
    } else if (mouse_b & 2) {
      show_mouse(0);
      map[mouse_x/16-5][mouse_y/16-2] = 0;
      // Bereich des Sprites schwarz ueberdecken
      rectfill(
        screen,
        fit16x(mouse_x), fit16y(mouse_y),
        fit16x(mouse_x)+15, fit16y(mouse_y) + 15,
        0
        );

      show_mouse(screen);
    } // if (mouse_b & 1) else if (mouse_b & 2)

    if (keypressed()) {
      c = readkey();
      repaint_status_line = FALSE;
      show_mouse(0);

      switch (c) {
        case 'r':
          repaint_map = TRUE;
          break;
        case ESC:
          KILL_STATUS_LINE;
          status_line("Programm beenden? [j/n]");
          repaint_status_line = TRUE;
          c = readkey();
          if (c == 'j')
            exit_zeldapaint = TRUE;
          break;
        case 'x':
          --index;
          repaint_status_line = TRUE;
          break;
        case 'c':
          ++index;
          repaint_status_line = TRUE;
          break;
        case 's':
          KILL_STATUS_LINE;
          repaint_status_line = TRUE;
          getstring(Datei);
          strcat(Datei, ".map");
          if (exist(Datei)) {
            sprintf (buf, "\"%s\" ueberschreiben [J/N]", Datei);
            status_line(buf);
            c = readkey();
            if (c != 'j')
              break;
          }
          KILL_STATUS_LINE;
          sprintf (buf, "Save: \"%s\"", Datei);
          status_line(buf);
          save_map(Datei, map);
          for (i=0; Datei[i] != '.'; ++i);
          Datei[i] = '\0';
          strcat(Datei, ".pcx");
          save_bitmap(Datei, save_bmp, my_pallete);
          break;
        case 'l':
          KILL_STATUS_LINE;
          getstring(Datei);
          strcat(Datei, ".map");
          if (exist(Datei)) {
            load_map(Datei, map);
            repaint_map = TRUE;
          } else {
            sprintf(buf, "Fehler: \"%s\"", Datei);
            status_line(buf);
            readkey();
          }
          repaint_status_line = TRUE;
          break;
      } // switch(c)
      show_mouse(screen);
    } // if (keypressed())

    if (index > maxSprite)
      index = maxSprite;
    else if (index < minSprite)
      index = minSprite;

    if (repaint_map) {
      show_mouse(0);
      for (y=0; y<8; ++y)
        for (x=0; x<10; ++x) {
          sprite_bmp = load_bmp_with_check(Sprite[map[x][y]], my_pallete);
          blit (sprite_bmp, screen,
                0,0,
                x*16+80, y*16+32,
                16, 16
            );
        }
      sprite_bmp = load_bmp_with_check(Sprite[index], my_pallete);
      show_mouse(screen);
      repaint_map = FALSE;
    } // repaint_map

    if (repaint_status_line) {
      show_mouse(0);
      sprite_bmp = load_bmp_with_check(Sprite[index], my_pallete);
      /* Dateiname des Sprites ausgeben */
      KILL_STATUS_LINE;
      sprintf (buf, "%3d - %s", index, Sprite[index] + strlen(Pfad));
      status_line(buf);

      blit (sprite_bmp, screen,
            0,0,
            0, 0,
            16, 16
        );

      show_mouse(screen);
      repaint_status_line = FALSE;
    } // if (repaint_status_line)
  } // while (!exit_zeldapaint)
  allegro_exit();
  printf ("Programm beendet.");
  return 0;
} // main
