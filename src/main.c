
#include <curses.h>
#include <time.h>

static const int KEY_RETURN = 10;
static const int DEFAULT_COLORS = 1;
static const int HIGHLIGHT_COLORS = 2;

// see http://hughm.cs.ukzn.ac.za/~murrellh/os/notes/ncurses.html

static void millissleep(int millis) {
  struct timespec ts = {
    .tv_sec=0, 
    .tv_nsec = millis * 1000000
  };
  nanosleep(&ts, NULL);
}

static void default_color(WINDOW *win) {
  wattron(win, COLOR_PAIR(DEFAULT_COLORS));
}

static void highlight_color(WINDOW *win) {
  wattron(win, COLOR_PAIR(HIGHLIGHT_COLORS));
}

void init_colors() {
  // this must be called before using colors
  start_color();

  init_pair(DEFAULT_COLORS, COLOR_WHITE, COLOR_BLACK);
  init_pair(HIGHLIGHT_COLORS, COLOR_MAGENTA, COLOR_BLACK);
}

void init(WINDOW *win) {
  init_colors();
  keypad(win, TRUE);
  keypad(stdscr, TRUE);
  // turn off normal echoing to allow the letters to be placed manually
  noecho();
}

int main(int argc, const char* argv[]) {

  printf("test\n");

  // printf won't work after this
  initscr();

  int lines = 10;
  int cols = 50;

  // upper left corner
  int y0 = 10;
  int x0 = 10;


  WINDOW *win = newwin(lines, cols, y0, x0);
  init(win);

  // get height and width of window
  /*
  int h, w;
  getmaxyx(win, h, w);
  */

  // ascii character
  int ch;
  while((ch = getch()) != KEY_RETURN) {
    int c = ch;
    if (ch == 't') {
      default_color(win);
      c = c | A_UNDERLINE;  //| COLOR_PAIR(3);
      //A_NORMAL        Normal display (no highlight)
      //A_STANDOUT      Best highlighting mode of the terminal.
      //A_UNDERLINE     Underlining
      //A_REVERSE       Reverse video
      //A_BLINK         Blinking
      //A_DIM           Half bright
      //A_BOLD          Extra bright or bold
      //A_PROTECT       Protected mode
      //A_INVIS         Invisible or blank mode
      //A_ALTCHARSET    Alternate character set
      //A_CHARTEXT      Bit-mask to extract a character
      //COLOR_PAIR(n)   Color-pair number n
      //int yTo = 8, xTo = 40;
      //wmove(win, 0, 0);
    } else {
      highlight_color(win);
      //wmove(win, 10, 0);
    }
    waddch(win, c);
    // must be called to flush changes
    wrefresh(win);
  }

  //millissleep(5000);

  // move cursor
  //int yTo = 8, xTo = 40;
  //wmove(win, yTo,  xTo);
 
  endwin();

  /*
  switch(ch) {
    case KEY_ENTER: 
      printf("keypad enter\n");
      break;
    case KEY_DOWN:
      printf("down\n");
      break;
    case KEY_RETURN:
      printf("enter\n");
    default:
      printf("unknown key: %c\n", ch);
  }
  */

  //printf("done %s\n", str);

  return 1;
}

