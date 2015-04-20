#include <stdio.h>
#include <string.h>
#include <allegro.h>

#define frand() (float)rand()/RAND_MAX
#define invinitive while(TRUE)
#define rnd(a) (int)(frand()*a)
#define maxSprite 60
#define minSprite 0
#define fit16x(a) ((a/16)*16)
#define fit16y(a) (((a-16)/16)*16+16)

/*int fit16(int zahl)
{
  return zahl/16*16;
}*/

void main(void)
{
  PALLETE my_pallete;
  int index;
  BITMAP *sprite_bmp;
  BITMAP *save_bmp;
  char Sprite[maxSprite+1][30];
  char Pfad[14];
  char Datei[14];
  char buf[20];
  char c;
  FILE *in;

  // liest Sprite Namen aus Datei ein
  in = fopen("sprite.ini", "r");
  strcpy(Pfad, "Sprite\\");
  for (index=0; index <= maxSprite; ++index) {
    fscanf(in, "%s", Datei);
    strcpy(Sprite[index], Pfad);
    strcat(Sprite[index], Datei);
//  printf("%s\n", Sprite[index]); 
  }
  fclose(in);

  allegro_init();
  install_keyboard(); 
  install_mouse(); 
  install_timer();

  set_gfx_mode(GFX_VGA, 320, 200, 0, 0);
  set_mouse_speed(0,0);
  set_mouse_range(80, 32, 239, 159);
  freeze_mouse_flag=0;

  clear(screen);
  index = minSprite;   
  save_bmp = create_sub_bitmap(screen, 80, 32, 160, 128);
  sprite_bmp = load_bmp(Sprite[index], my_pallete);
  set_pallete (my_pallete);
  clear(screen);

  blit (sprite_bmp, screen, 0, 0, 0, 0, 16, 16); 
  sprintf (buf, "%3d - %s", index, Sprite[index] + strlen(Pfad));
  textout(screen, font, buf, 50, 1, 255);
  hline(screen, 0, 22, 319, 255);
  rect(screen, 79, 31, 240, 160,50);

  while(!key[KEY_ESC]) {
     show_mouse(screen);
     if (mouse_b & 1) {
       show_mouse(0);
       blit (sprite_bmp, screen, 0,0, fit16x(mouse_x), fit16y(mouse_y), 16, 16);
     } else if (mouse_b & 2) {
       show_mouse(0);
       rectfill(screen, fit16x(mouse_x), fit16y(mouse_y),  fit16x(mouse_x)+15, fit16y(mouse_y)+15, 0);
     }
     if (keypressed()) {
       c = readkey();

       switch (c) {
         case 'x': --index; break;
         case 'c': ++index; break;
         case 's':
           show_mouse(0);
           textout(screen, font, "!saving bmp!", 50, 1, 255);
           save_bitmap("dump.bmp", save_bmp, my_pallete);
           break;
       }

       if (index > maxSprite)
         index = maxSprite;
       else if (index < minSprite)
         index = minSprite;

       sprite_bmp = load_bmp(Sprite[index], my_pallete);
       textout(screen, font, "                  ", 50, 1, 255);
       sprintf (buf, "%3d - %s", index, Sprite[index] + strlen(Pfad));
       textout(screen, font, buf, 50, 1, 255);
       blit (sprite_bmp, screen, 0,0, 0, 0, 16, 16); 
     }
  }
   allegro_exit();
}
