// Pseudo-Funktionen
#define frand() (float)rand()/RAND_MAX
#define rnd(a) (int)(frand()*a)
#define fit16x(a) ((a/16)*16)
#define fit16y(a) (((a-16)/16)*16+16)
#define fit16(a) ((a/16)*16)
#define KILL_STATUS_LINE rectfill(screen, 17, 0, 319, 20,0);
#define exist(a) !access(a,00)
#define status_line(buf) textout(screen, font, buf, 50, 1, 255)

// Konstanten
#define maxSprite 60
#define minSprite 0
#define ESC 27
