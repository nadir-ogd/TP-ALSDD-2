  /**--------------------------------------------------------**/
  /**       C o n v e r s i o n   Z vers C (Standard)        **/
  /**             Réalisée par Pr D.E ZEGOUR                 **/
  /**             E S I - Alger                              **/
  /**             Copywrite 2020                             **/
  /**--------------------------------------------------------**/

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <stdio.h>
  #include <windows.h>
  #define east 35
  #define center 42
  #define ouest 31
  typedef int bool ;
  typedef char * string255 ;
  typedef char * string2 ;
  #define True 1
  #define False 0



/*          _______________________________________________________________________________________________________
            |                                                                                                       |
            |                                    _______________________________                                    |
            |                                   |                               |                                   |
            |                                   |       INTERFACE GRAPHIQUE     |                                   |
            |                                   |_______________________________|                                   |
            |                                                                                                       |
            |                                                                                                       |
            |_______________________________________________________________________________________________________|                  */




typedef struct C_G C_G ;
struct C_G
{ char tab[7][100];
  int nb;
};
typedef struct chaine chaine;
struct chaine
 {
     char  mots[100];
 };


//----------------------------------Bibliotheque Conio pour l'interface graphique ----------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
typedef enum
{
    BLACK,          /**< black color */
    BLUE,           /**< blue color */
    GREEN,          /**< green color */
    CYAN,           /**< cyan color */
    RED,            /**< red color */
    MAGENTA,        /**< magenta color */
    BROWN,          /**< brown color */
    LIGHTGRAY,      /**< light gray color */
    DARKGRAY,       /**< dark gray color */
    LIGHTBLUE,      /**< light blue color */
    LIGHTGREEN,     /**< light green color */
    LIGHTCYAN,      /**< light cyan color */
    LIGHTRED,       /**< light red color */
    LIGHTMAGENTA,   /**< light magenta color */
    YELLOW,         /**< yellow color */
    WHITE           /**< white color */
} COLORS;

/*@{*/
/**
 * This defines enables you to use all MinGW conio.h functions without
 * underscore.
 */
#define cgets   _cgets
#define cprintf _cprintf
#define cputs   _cputs
#define cscanf  _cscanf

#ifdef UNICODE
    #define cgetws   _cgetws
    #define getwch   _getwch
    #define getwche  _getwche
    #define putwch   _putwch
    #define ungetwch _ungetwch
    #define cputws   _cputws
    #define cwprintf _cwprintf
    #define cwscanf  _cwscanf
#endif
/*@}*/

/**
 * Define alias for _conio_gettext.
 * If you want to use gettext function from some other library
 * (e.g. GNU gettext) you have to define _CONIO_NO_GETTEXT_ so you won't get
 * name conflict.
 */
#ifndef _CONIO_NO_GETTEXT_
  #define gettext _conio_gettext
#endif

#define ScreenClear clrscr

/**
 * @anchor cursortypes
 * @name Cursor types
 * Predefined cursor types. */
/*@{*/
#define _NOCURSOR 0         /**< no cursor */
#define _SOLIDCURSOR 100    /**< cursor filling whole cell */
#define _NORMALCURSOR 20    /**< cursor filling 20 percent of cell height */
/*@}*/

/**
 * Structure holding information about screen.
 * @see gettextinfo
 * @see inittextinfo
 */
struct text_info {
    unsigned char curx;          /**< cursor coordinate x */
    unsigned char cury;          /**< cursor coordinate y */
    unsigned short attribute;    /**< current text attribute */
    unsigned short normattr;     /**< original value of text attribute after
                                      start of the application. If you don't
                                      called the <TT>inittextinfo</TT> on the
                                      beginning of the application, this always
                                      will be black background and light gray
                                      foreground */
    unsigned char screenwidth;   /**< screen width */
    unsigned char screenheight;  /**< screen height */
};

/**
 * Structure used by gettext/puttext.
 * @see _conio_gettext
 * @see puttext
 */
struct char_info {
#ifdef UNICODE
    wchar_t letter;        /**< character value */
#else
    char letter;           /**< character value */
#endif
    unsigned short attr;   /**< attribute value */
};

static int __BACKGROUND = BLACK;
static int __FOREGROUND = LIGHTGRAY;
static struct text_info __text_info = {
    1, 1,
    LIGHTGRAY + (BLACK << 4),
    LIGHTGRAY + (BLACK << 4),
    80, 25
};
static int __CONIO_TOP = 0;
static int __CONIO_LEFT = 0;

static void
__fill_text_info (void)
{
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    __CONIO_LEFT = info.srWindow.Left;
    __CONIO_TOP = info.srWindow.Top;
    __text_info.curx = info.dwCursorPosition.X - __CONIO_LEFT + 1;
    __text_info.cury = info.dwCursorPosition.Y - __CONIO_TOP  + 1;
    __text_info.attribute = info.wAttributes;
    __text_info.screenwidth  = info.srWindow.Right - info.srWindow.Left + 1;
    __text_info.screenheight = info.srWindow.Bottom - info.srWindow.Top + 1;
}

void
gettextinfo (struct text_info * info)
{
    __fill_text_info();
    *info = __text_info;
}

void
inittextinfo (void)
{
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo (GetStdHandle(STD_OUTPUT_HANDLE), &info);
    __text_info.normattr = info.wAttributes;
}

void
clrscr (void)
{
    DWORD written;
    int i;

    __fill_text_info();
    for (i = __CONIO_TOP; i < __CONIO_TOP + __text_info.screenheight; i++) {
      FillConsoleOutputAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
        __FOREGROUND + (__BACKGROUND << 4), __text_info.screenwidth,
        (COORD) {__CONIO_LEFT, i},
        &written);
      FillConsoleOutputCharacter (GetStdHandle(STD_OUTPUT_HANDLE), ' ',
        __text_info.screenwidth,
        (COORD) {__CONIO_LEFT, i},
        &written);
    }
    gotoxy (1, 1);
}


void
clreol (void)
{
    COORD coord;
    DWORD written;

    __fill_text_info();
    coord.X = __CONIO_LEFT + __text_info.curx - 1;
    coord.Y = __CONIO_TOP  + __text_info.cury - 1;

    FillConsoleOutputAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
      __FOREGROUND + (__BACKGROUND << 4),
      __text_info.screenwidth - __text_info.curx + 1, coord, &written);
    FillConsoleOutputCharacter (GetStdHandle (STD_OUTPUT_HANDLE),
      ' ', __text_info.screenwidth - __text_info.curx + 1, coord, &written);
    gotoxy (__text_info.curx, __text_info.cury);
}


void
delline (void)
{
    COORD coord;
    SMALL_RECT rect;
    CHAR_INFO fillchar;

    __fill_text_info();
    coord.X = __CONIO_LEFT;
    coord.Y = __CONIO_TOP + __text_info.cury - 1;
    rect.Left = __CONIO_LEFT;
    rect.Top = __CONIO_TOP + __text_info.cury;
    rect.Right = __CONIO_LEFT + __text_info.screenwidth - 1;
    rect.Bottom = __CONIO_TOP + __text_info.screenheight - 1;
    fillchar.Attributes = __FOREGROUND + (__BACKGROUND << 4);
#ifdef UNICODE
    fillchar.Char.UnicodeChar = L' ';
    ScrollConsoleScreenBufferW (GetStdHandle (STD_OUTPUT_HANDLE),
      &rect, NULL, coord, &fillchar);
#else
    fillchar.Char.AsciiChar = ' ';
    ScrollConsoleScreenBufferA (GetStdHandle (STD_OUTPUT_HANDLE),
      &rect, NULL, coord, &fillchar);
#endif


    gotoxy (__text_info.curx, __text_info.cury);
}

void
insline (void)
{
    COORD coord;
    SMALL_RECT rect;
    CHAR_INFO fillchar;

    __fill_text_info();
    coord.X = __CONIO_LEFT;
    coord.Y = __CONIO_TOP + __text_info.cury;
    rect.Left = __CONIO_LEFT;
    rect.Top = __CONIO_TOP + __text_info.cury - 1;
    rect.Right = __CONIO_LEFT + __text_info.screenwidth - 1;
    rect.Bottom = __CONIO_TOP + __text_info.screenheight - 2;
    fillchar.Attributes = __FOREGROUND + (__BACKGROUND << 4);
#ifdef UNICODE
    fillchar.Char.UnicodeChar = L' ';
    ScrollConsoleScreenBufferW (GetStdHandle (STD_OUTPUT_HANDLE),
      &rect, NULL, coord, &fillchar);
#else
    fillchar.Char.AsciiChar = ' ';
    ScrollConsoleScreenBufferA (GetStdHandle (STD_OUTPUT_HANDLE),
      &rect, NULL, coord, &fillchar);
#endif

    gotoxy (__text_info.curx, __text_info.cury);
}

void
movetext (int left, int top, int right, int bottom, int destleft, int desttop)
{
    struct char_info * buffer;

    buffer = malloc ((right - left + 1) * (bottom - top + 1) * sizeof(struct char_info));
    gettext (left, top, right, bottom, buffer);
    puttext (destleft, desttop, destleft + right - left, desttop + bottom - top, buffer);
    free(buffer);
}

void
_conio_gettext (int left, int top, int right, int bottom,
  struct char_info * buf)
{
    int i;
    SMALL_RECT r;
    CHAR_INFO* buffer;
    COORD size;

    __fill_text_info();
    r = (SMALL_RECT) {__CONIO_LEFT + left - 1, __CONIO_TOP + top - 1,
      __CONIO_LEFT + right - 1, __CONIO_TOP + bottom - 1};
    size.X = right - left + 1;
    size.Y = bottom - top + 1;
    buffer = malloc (size.X * size.Y * sizeof(CHAR_INFO));

    ReadConsoleOutput (GetStdHandle (STD_OUTPUT_HANDLE),
      (PCHAR_INFO) buffer, size, (COORD) {0, 0}, &r);

    for (i = 0; i < size.X * size.Y; i++)
    {
#ifdef UNICODE
        buf[i].letter = buffer[i].Char.UnicodeChar;
#else
        buf[i].letter = buffer[i].Char.AsciiChar;
#endif
        buf[i].attr = buffer[i].Attributes;
    }
    free (buffer);
}

void
puttext (int left, int top, int right, int bottom, struct char_info * buf)
{
    int i;
    SMALL_RECT r;
    CHAR_INFO* buffer;
    COORD size;

    __fill_text_info();
    r = (SMALL_RECT) {__CONIO_LEFT + left - 1, __CONIO_TOP + top - 1,
      __CONIO_LEFT + right - 1, __CONIO_TOP + bottom - 1};
    size.X = right - left + 1;
    size.Y = bottom - top + 1;
    buffer = malloc (size.X * size.Y * sizeof(CHAR_INFO));

    for (i = 0; i < size.X * size.Y; i++)
    {
#ifdef UNICODE
        buffer[i].Char.UnicodeChar = buf[i].letter;
#else
        buffer[i].Char.AsciiChar = buf[i].letter;
#endif
        buffer[i].Attributes = buf[i].attr;
    }

    WriteConsoleOutput (GetStdHandle (STD_OUTPUT_HANDLE),
      buffer, size, (COORD) {0, 0}, &r);
    free (buffer);
}

void
gotoxy(int x, int y)
{
  COORD c;

  c.X = __CONIO_LEFT + x - 1;
  c.Y = __CONIO_TOP  + y - 1;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void
cputsxy (int x, int y, char * str)
{
    gotoxy (x, y);
    cputs (str);
}

void
putchxy (int x, int y, char ch)
{
    gotoxy (x, y);
    putch (ch);
}

void
_setcursortype (int type)
{
    CONSOLE_CURSOR_INFO Info;

    if (type == 0) {
        Info.bVisible = FALSE;
    } else {
      Info.dwSize = type;
      Info.bVisible = TRUE;
    }
    SetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE),
      &Info);
}


void
textattr (int _attr)
{
    __FOREGROUND = _attr & 0xF;
    __BACKGROUND = _attr >> 4;
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), _attr);
}

void
normvideo (void)
{
    textattr (__text_info.normattr);
}

void
textbackground (int color)
{
    __BACKGROUND = color;
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
      __FOREGROUND + (color << 4));
}


void
textcolor (int color)
{
    __FOREGROUND = color;
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
      color + (__BACKGROUND << 4));
}


int
wherex (void)
{
    __fill_text_info();
    return __text_info.curx;
}


int
wherey (void)
{
    __fill_text_info();
    return __text_info.cury;
}

char *
getpass (const char * prompt, char * str)
{
    int maxlength = str[0];
    int length = 0;
    int ch = 0;
    int x, y;

    cputs(prompt);
    __fill_text_info();
    x = __text_info.curx;
    y = __text_info.cury;

    while (ch != '\r') {
        ch = getch();
        switch (ch) {
            case '\r' : /* enter */
                break;
            case '\b' : /* backspace */
                if (length > 0) putchxy (x + --length, y, ' ');
                gotoxy (x + length, y);
                break;
            default:
                if (length < maxlength) {
                    putchxy (x + length, y, '*');
                    str[2 + length++] = ch;
                }
        }
    }

    str[1] = length;
    str[2 + length] = '\0';
    return &str[2];
}

void
highvideo (void)
{
    if (__FOREGROUND < DARKGRAY) textcolor(__FOREGROUND + 8);
}

void
lowvideo (void)
{
    if (__FOREGROUND > LIGHTGRAY) textcolor(__FOREGROUND - 8);
}

void
delay (int ms)
{
    Sleep(ms);
}

void
switchbackground (int color)
{
    struct char_info* buffer;
    int i;

    buffer = malloc(__text_info.screenwidth * __text_info.screenheight *
      sizeof(struct char_info));
    _conio_gettext(1, 1, __text_info.screenwidth, __text_info.screenheight,
      buffer);
    for (i = 0; i < __text_info.screenwidth * __text_info.screenheight; i++) {
        unsigned short attr = buffer[i].attr & 0xF;
        buffer[i].attr = (color << 4) | attr;
    }
    puttext(1, 1, __text_info.screenwidth, __text_info.screenheight, buffer);
    free(buffer);
}

void
flashbackground (int color, int ms)
{
    struct char_info* buffer;

    buffer = malloc(__text_info.screenwidth * __text_info.screenheight *
      sizeof(struct char_info));
    _conio_gettext(1, 1, __text_info.screenwidth, __text_info.screenheight,
      buffer);
    switchbackground(color);
    delay(ms);
    puttext(1, 1, __text_info.screenwidth, __text_info.screenheight, buffer);
    free(buffer);
}

void
clearkeybuf (void)
{
    while (kbhit()) {
        getch();
    }
}

#ifdef __cplusplus
}
#endif
/*--------------------------------------Affichage------------------------------------------------*/

void decalrectangle(int much)
{   int y;
    if(much==1){y=11;}
    if(much==2){y=21;}
    if(much==3){y=31;}
    textbackground(15);
    textcolor(15);

    gotoxy(1,y-10);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y-9);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y-8);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y-7);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y-6);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y-5);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y-4);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y-3);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y-2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y-1);
    delay(10);
    textbackground(7);
    textcolor(7);
    gotoxy(1,y);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+1);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+3);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+4);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+5);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+6);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+7);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+8);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+9);
}

void moverect(char mot[4])
{   int i,y;
    if (strcmp(mot,"up")==0){y=35;
    for(i=0;i<25;i++){
        gotoxy(1,y-i);
        textcolor(7);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
        if(i!=0)
        {gotoxy(1,y-i+5);
        textbackground(15);
        textcolor(15);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
        textbackground(3);
        }delay(30);
    }}
    if(strcmp(mot,"down")==0)
    {y=10;
    for(i=0;i<25;i++){
        gotoxy(1,y+i);
        textcolor(7);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
        if(i!=0)
        {gotoxy(1,y+i);
        textbackground(15);
        textcolor(15);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
        textbackground(3);
        }delay(30);
    }
}
}



void intro(void)
{   int y;
    system("mode con lines=40 cols=120");
    y=1;
    textcolor((0));
  /*  gotoxy(1,y);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+1);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+3);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+4);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+5);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+6);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+7);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+8);
    //printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+9);
    delay(400);
    decalrectangle(2);*/
  //**********************************************************************************************************************
    //textbackground(15);
     int i,x,z,c;

    gotoxy(1,2);
    x=wherex();
    z=wherey();
    gotoxy(x,z);
    textbackground(0);
    textcolor(15);
    printf(" ______  _____  __ ");
    gotoxy(x,z+1);
    printf("|  ____|/ ____||__|");
    gotoxy(x,z+2);
    printf("| |__  | (___   __ ");
    gotoxy(x,z+3);
    printf("|  __|  \\___ \\ |  |");
    gotoxy(x,z+4);
    printf("| |____ ____) ||  |");
    gotoxy(x,z+5);
    printf("|______|_____/ |__|");
    textcolor(9);
    gotoxy(x+15,z);
    printf(" __");
    gotoxy(x+15,z+1);
    printf("|__|");
    textcolor(15);
    gotoxy(x+21,z+1);
    printf("%ccole nationale",144);
    gotoxy(x+21,z+3);
    printf("Sup%crieure",130);
    gotoxy(x+21,z+5);
    printf("d'Informatique");
    //textbackground(0);
   // printdirection("Ecole Nationale Superieur en Informatique d'Alger ","right",40,1,30);
    printdirection("Annee Universitaire :","right",95,4,30);
    textcolor(9);
    textbackground(0);
    printdirection("2019/2020","right",101,5,40) ;
    //decalrectangle(2);
    textbackground(0);

    textcolor(9);
    gotoxy(14,10);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
    gotoxy(14,11);
    printf("%c                                                                                            %c\n",186,186);gotoxy(14,12);
    printf("%c                                                                                            %c\n",186,186);gotoxy(14,13);
    printf("%c                                                                                            %c\n",186,186);gotoxy(14,14);
    printf("%c                                                                                            %c\n",186,186);gotoxy(14,15);
    printf("%c                                                                                            %c\n",186,186);gotoxy(14,16);
    printf("%c                                                                                            %c\n",186,186);gotoxy(14,17);
    printf("%c                                                                                            %c\n",186,186);gotoxy(14,18);
    printf("%c                                                                                            %c\n",186,186);gotoxy(14,19);
    printf("%c                                                                                            %c\n",186,186);gotoxy(14,20);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);

    textbackground(0);
    textcolor(9);
    gotoxy(35,12);
    printf("%c%c%c%c%c%c%c%c%c%c         %c%c%c%c%c%c%c%c%c               %c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219) ;delay(50);gotoxy(35,13);
    printf("    %c%c             %c%c     %c%c                     %c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);delay(50);gotoxy(35,14);
    printf("    %c%c             %c%c     %c%c                     %c%c\n",219,219,219,219,219,219,219,219);delay(50);gotoxy(35,15);
    printf("    %c%c             %c%c%c%c%c%c%c%c%c               %c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);delay(50);gotoxy(35,16);
    printf("    %c%c             %c%c                      %c%c\n",219,219,219,219,219,219,219);delay(50);gotoxy(35,17);
    printf("    %c%c             %c%c                      %c%c\n",219,219,219,219,219,219,219);delay(50);gotoxy(35,18);
    printf("    %c%c             %c%c                      %c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219);



   /* delay(300);
    decalrectangle(3);
    textbackground(15);
    textcolor(0);*/

    textbackground(0);
    textcolor(9);
     gotoxy(14,20);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);gotoxy(14,21);
    printf("%c                                                                                            %c\n",186,186);gotoxy(14,22);
    printf("%c                                                                                            %c\n",186,186);gotoxy(14,23);
    printf("%c                                                                                            %c\n",186,186);gotoxy(14,24);
    printf("%c                                                                                            %c\n",186,186);gotoxy(14,25);
    printf("%c                                                                                            %c\n",186,186);gotoxy(14,26);
    printf("%c                                                                                            %c\n",186,186);gotoxy(14,27);
    printf("%c                                                                                            %c\n",186,186);gotoxy(14,28);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
    textbackground(0);
    textcolor(15);
    printdirection(">","down",20,22,35);
    textbackground(0);
    textcolor(15);
    printdirection("REALISE PAR : ","left",35,22,35);
    textbackground(0);
    textcolor(9);
    printdirection("N   " ,"down",71,23,35);
    textbackground(0);
    printdirection("I   " ,"down",70,23,35);
    textbackground(0);
    printdirection("M   " ,"down",69,23,35);
    textbackground(0);
    printdirection("A   " ,"down",68,23,35);
    textbackground(0);
    printdirection("L   " ,"down",67,23,35);
    textbackground(0);
    printdirection("E   ","down",66,23,35);
    textbackground(0);
    printdirection("D   ","down",65,23,35);
    textbackground(0);
    printdirection("E   ","down",64,23,35);
    textbackground(0);
    printdirection("MR  ","down",63,23,35);
    textbackground(0);
    printdirection("AI  ","down",62,23,35);
    textbackground(0);
    printdirection("HD  ","down",61,23,35);
    textbackground(0);
    printdirection("OA5 ","down",60,23,35);
    textbackground(0);
    printdirection("MNB ","down",59,23,35);
    textbackground(0);
    textcolor(15);
    printdirection("||| ","down",55,23,35);
    textcolor(9);
    textbackground(0);
    printdirection("A   ","down",52,23,35);
    textbackground(0);
    printdirection("FD  ","down",51,23,35);
    textbackground(0);
    printdirection("REE ","down",50,23,35);
    textbackground(0);
    printdirection("EUP ","down",49,23,35);
     textbackground(0);
    printdirection("KGU ","down",48,23,35);
    textbackground(0);
    printdirection("UAO ","down",47,23,35);
    textbackground(0);
    printdirection("OUR ","down",46,23,35);
    textbackground(0);
    printdirection("BOG ","down",45,23,35);
    textbackground(0);
    textcolor(15);
    printdirection("<< STATISTIQUES SUR COVID-19 >>","right",73,25,30);
    textbackground(0);
    printdirection("> ENCADRE PAR :","right",20,27,25);
    textbackground(0);
    textcolor(9);
    printdirection("Dr M.BOULAKARADECHE & Dr DE.ZEGOUR","right",50,27,25);
    gotoxy(wherex()-30,wherey()+6);
     textbackground(15);
     textcolor(0);
     gotoxy(40,33);
    system("pause");
}

void fin(void)
{   system("COLOR F7");
    system("cls");
    decalrectangle(1);
    moverect("down");
    moverect("up");
    textbackground(15);
    textcolor(0);
    printdirection("           Fin du programme, merci !    ","right",33,2,30 );
    delay(1000);
    decalrectangle(2);
    decalrectangle(3);
    gotoxy(15,10);
    textbackground(7);
    textcolor(15);
    printdirection(" Pour toute remarque contactez nous sur : ","right",wherex()+25,wherey(),20);textbackground(7);
    printdirection("       ","down",60,wherey()+4,15);
    textbackground(0);textcolor(15);
    printdirection(" BOUKERFA MOHAMED ELAMIN ","right",20,16,15);
    textbackground(15);textcolor(0);
    printdirection(" e-mail: jm_boukerfa@esi.dz ","right",20,18,15);
    textbackground(0);textcolor(15);
    printdirection(" OUAGUED NADIR ","right",80,16,15);
    textbackground(15);textcolor(0);
    printdirection(" e-mail: jn_ouagued@esi.dz ","right",80,18,15);


    gotoxy(wherex(),wherey()+2);
    textcolor(0);
    gotoxy(20,40);
    printf("copyright 2020");
    gotoxy(80,28);
    system("pause");
}

void printdirection(char mot[120],char direction[6],int x ,int y ,int delai) //Impression dans une direction donnée
{   int i;
    if(strcmp(direction,"up")==0)
    {for(i=0;i<strlen(mot);i++)
        {gotoxy(x,y-i);
        printf("%c",mot[i]);
        delay(delai);}
    }
    if(strcmp(direction,"down")==0)
    {for(i=0;i<strlen(mot);i++)
        {gotoxy(x,y+i);
        printf("%c",mot[i]);
        delay(delai);}
    }
    if(strcmp(direction,"right")==0)
    {for(i=0;i<strlen(mot);i++)
        {gotoxy(x+i,y);
        printf("%c",mot[i]);
        delay(delai);}
    }
    if(strcmp(direction,"left")==0)
    {for(i=0;i<strlen(mot);i++)
        {gotoxy(x-i,y);
        printf("%c",mot[strlen(mot)-i-1]);
        delay(delai);}
    }
    textbackground(15);
}

int choix_1 (void)
{   int i,x=0,y=0,ch;
    chaine lechoix[]={ "   >>  Creer La premiere structure(Tableau 10 P)  <<  ",
                       "   >>        Afficher La premeiere structure      <<  ",
                       "   >>          Creer La deuxieme structure        <<  ",
                       "   >>        Afficher La deuxieme structure       <<  ",
                       "   >>                  Pourcentage                <<  ",
                       "   >>                      Exit                   <<  ",};
    ch = 1;
    do{
        for(i=0;i<6;i++)
            {if(i==ch){
            textbackground(0);
            textcolor(15);
            printdirection(lechoix[i].mots,"right",35,(22+i+1),0);
            }
  else{
            textbackground(8);
            textcolor(0);
            printdirection(lechoix[i].mots,"right",35,(22+i+1),0);
            }
        }
        x=readkey();
        switch(x){
            case 336 : ch = (ch+1)%6;
                break;
            case 328: ch = (ch+5)%6;
               break;
            case 13 :
                y=1;
            break;
       }
    }while(y!=1);

    return ch+1;
}

int readkey(void) //Lit une touche du clavier
{   int key;
    clearkeybuf();
    key=getch();
    if (key==0){
        key=getch()+256;}
    if( key==224){
        key=getch()+256;}
    return key;
}

void  basemenu_1(void)
{   int i,y,a=0,z,d,b;
    system("mode con lines=40 cols=120");
    system("cls");
    system("COLOR F7");
    blancln(2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    moverect("down");
    moverect("up");
    textbackground(7);
    textcolor(15);
    y=7;
    gotoxy(35,y);
    printf("%c%c%c%c%c   %c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c     %c%c%c%c   %c%c%c   %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+1);
    printf("%c%c%c%c%c%c %c%c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c%c    %c%c%c%c   %c%c%c   %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c   %c%c%c        %c%c%c%c%c%c   %c%c%c%c   %c%c%c   %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+3);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c  %c%c%c%c   %c%c%c   %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+4);
    printf("%c%c%c  %c%c%c  %c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c %c%c%c%c   %c%c%c   %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+5);
    printf("%c%c%c   %c   %c%c%c   %c%c%c        %c%c%c%c  %c%c%c%c%c%c%c   %c%c%c   %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+6);
    printf("%c%c%c       %c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c    %c%c%c%c%c   %c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+7);
    printf("%c%c%c       %c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c     %c%c%c%c    %c%c%c%c%c%c%c ",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    /*gotoxy(30,20);
    textcolor(7);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,22);delay(50);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,23);delay(50);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,24);delay(50);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,25);delay(50);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,26);delay(50);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,27);delay(50);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,28);delay(50);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,29);delay(50);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,30);delay(50);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,31);delay(50);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,32);delay(50);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,34);delay(50);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    */
    textcolor(15);
    z=89;
    d=20;
    /*textbackground(15);
    b=0;  textbackground(b);*/

    printdirection("                                                     \n","left",z,d+2,0);textbackground(15);
    printdirection("                                                     \n","left",z,d+3,0);textbackground(15);
    printdirection("                                                     \n","left",z,d+4,0);textbackground(15);
    printdirection("                                                     \n","left",z,d+5,0);textbackground(15);
    printdirection("                                                     \n","left",z,d+6,0);textbackground(15);
    printdirection("                                                     \n","left",z,d+7,0);textbackground(15);
}

int choix_2 (void)
{   int i,x=0,y=0,ch;
    chaine lechoix[]={ "   >>                 Creer la structure (Tableau 100 P)                <<  ",
                       "   >>                       Afficher la structure                       <<  ",
                       "   >>                               Exit                                <<  ",};

    ch = 1;
    do{
        for(i=0;i<3;i++)
            {if(i==ch){
            textbackground(0);
            textcolor(15);
            printdirection(lechoix[i].mots,"right",23,(22+i+1),0);
            }
        else{
            textbackground(8);
            textcolor(0);
            printdirection(lechoix[i].mots,"right",23,(22+i+1),0);
            }
        }
        x=readkey();
        switch(x){
            case 336 : ch = (ch+1)%3;
                break;
            case 328: ch = (ch+2)%3;
               break;
            case 13 :
                y=1;
            break;
       }
    }while(y!=1);

    return ch+1;
}

void  basemenu_2(void)
{   int i,y,a=0,z,d,b;
    system("mode con lines=40 cols=120");
    system("cls");
    system("COLOR F7");
    blancln(2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    moverect("down");
    moverect("up");
    textbackground(7);
    textcolor(15);
    y=7;
    gotoxy(35,y);
    printf("%c%c%c%c%c   %c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c     %c%c%c%c   %c%c%c   %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+1);
    printf("%c%c%c%c%c%c %c%c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c%c    %c%c%c%c   %c%c%c   %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c   %c%c%c        %c%c%c%c%c%c   %c%c%c%c   %c%c%c   %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+3);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c  %c%c%c%c   %c%c%c   %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+4);
    printf("%c%c%c  %c%c%c  %c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c %c%c%c%c   %c%c%c   %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+5);
    printf("%c%c%c   %c   %c%c%c   %c%c%c        %c%c%c%c  %c%c%c%c%c%c%c   %c%c%c   %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+6);
    printf("%c%c%c       %c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c    %c%c%c%c%c   %c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+7);
    printf("%c%c%c       %c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c     %c%c%c%c    %c%c%c%c%c%c%c ",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    /*gotoxy(30,20);
    textcolor(7);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,22);delay(50);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,23);delay(50);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,24);delay(50);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,25);delay(50);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,26);delay(50);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,27);delay(50);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,28);delay(50);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,29);delay(50);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,30);delay(50);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,31);delay(50);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,32);delay(50);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,34);delay(50);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    */
    textcolor(15);
    z=93;
    d=20;
    /*textbackground(15);
    b=0;  textbackground(b);*/
          printdirection("                                                                \n","left",z,d+2,0);textbackground(15);
          printdirection("                                                                \n","left",z,d+3,0);textbackground(15);
          printdirection("                                                                \n","left",z,d+4,0);textbackground(15);

}


int choix_partie (void)
{   int i,x=0,y=0,ch;
    chaine lechoix[]={ "   >>             PARTIE Z            <<  ",
                       "   >>             PARTIE C            <<  ",
                       "   >>               Exit              <<  ",};

    ch = 1;
    do{
        for(i=0;i<3;i++)
            {if(i==ch){
            textbackground(0);
            textcolor(15);
            printdirection(lechoix[i].mots,"right",40,(22+i+1),0);
            }
        else{
            textbackground(8);
            textcolor(0);
            printdirection(lechoix[i].mots,"right",40,(22+i+1),0);
            }
        }
        x=readkey();
        switch(x){
            case 336 : ch = (ch+1)%3;
                break;
            case 328: ch = (ch+2)%3;
               break;
            case 13 :
                y=1;
            break;
       }
    }while(y!=1);

    return ch+1;
}

void retourMenu() // Affiche un message pour retourner au menu
{
    printf("APPUYEZ SUR N'IMPORTE QUELLE TOUCHE POUR RETOURNER AU MENU!\n");
    getchar();
}


void  basemenu_partie(void)
{   int i,y,a=0,z,d,b;
    system("mode con lines=40 cols=120");
    system("cls");
    system("COLOR F7");
    blancln(2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    moverect("down");
    moverect("up");
    textbackground(7);
    textcolor(15);
    y=7;
    gotoxy(35,y);
    printf("%c%c%c%c%c   %c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c     %c%c%c%c   %c%c%c   %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+1);
    printf("%c%c%c%c%c%c %c%c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c%c    %c%c%c%c   %c%c%c   %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c   %c%c%c        %c%c%c%c%c%c   %c%c%c%c   %c%c%c   %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+3);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c  %c%c%c%c   %c%c%c   %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+4);
    printf("%c%c%c  %c%c%c  %c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c %c%c%c%c   %c%c%c   %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+5);
    printf("%c%c%c   %c   %c%c%c   %c%c%c        %c%c%c%c  %c%c%c%c%c%c%c   %c%c%c   %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+6);
    printf("%c%c%c       %c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c    %c%c%c%c%c   %c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+7);
    printf("%c%c%c       %c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c     %c%c%c%c    %c%c%c%c%c%c%c ",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);



  textbackground(15);
    textcolor(0);
    gotoxy(14,20);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);gotoxy(14,21);
    printf("%c                                                                                            %c\n",186,186);gotoxy(14,22);
    printf("%c                                                                                            %c\n",186,186);gotoxy(14,23);
    printf("%c                                                                                            %c\n",186,186);gotoxy(14,24);
    printf("%c                                                                                            %c\n",186,186);gotoxy(14,25);
    printf("%c                                                                                            %c\n",186,186);gotoxy(14,26);
    printf("%c                                                                                            %c\n",186,186);gotoxy(14,27);
    printf("%c                                                                                            %c\n",186,186);gotoxy(14,28);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);

    //textcolor(15);
    z=86;
    d=20;


    printdirection("                                                  \n","left",z+4,d+2,0);textbackground(15);
    printdirection("                                                  \n","left",z+4,d+2,0);textbackground(15);
    printdirection("                                                  \n","left",z+6,d+4,0);textbackground(15);

}

void blancln(int nombreln)
{   int i;
    for(i=0;i<nombreln;i++){printf(" \n");}
}

int choix_c_i (void)
{
    int i,x=0,y=0;
    textcolor(15);
    textbackground(0);
    printdirection("   Nombre de familles a generer   ","right",43,10,0); textbackground(7);
    printdirection("                    ","right",51,11,0); textbackground(7);
    printdirection("                    ","right",51,12,0); textbackground(7);
    printdirection("                    ","right",51,13,0);textbackground(7);

    do {
        textcolor(0);
        textbackground(15);
        printdirection("","right",58,12,0);

        gotoxy(60,12);
        scanf("%d", &i);
        //printf("%d",i);
        x=readkey();
        switch(x){
            case 336 :
                if(i>50){i-=10;}
            break;
            case 328:
                if(i<150){i+=10;}
            break;
            case 13 :
                y=1;
            break;
       }
 } while(y!=1);
 return i;
}





/*          _______________________________________________________________________________________________________
            |                                                                                                       |
            |                                    _______________________________                                    |
            |                                   |                               |                                   |
            |                                   |    FIN INTERFACE GRAPHIQUE    |                                   |
            |                                   |_______________________________|                                   |
            |                                                                                                       |
            |                                                                                                       |
            |_______________________________________________________________________________________________________|                  */







  /** Implémentation **\: TABLEAU DE ARBRES BINAIRES DE STRUCTURES**/

  /** Structures statiques **/

  typedef struct Tssic Type_Tssic  ;
  typedef Type_Tssic * Typestr_Tssic ;
  typedef string255 Type1_Tssic  ;
  typedef string255 Type2_Tssic  ;
  typedef int Type3_Tssic  ;
  typedef string2 Type4_Tssic  ;
  struct Tssic
    {
      Type1_Tssic Champ1 ;
      Type2_Tssic Champ2 ;
      Type3_Tssic Champ3 ;
      Type4_Tssic Champ4 ;
    };

  Type1_Tssic Struct1_Tssic ( Typestr_Tssic S)
    {
      return  S->Champ1 ;
    }

  Type2_Tssic Struct2_Tssic ( Typestr_Tssic S)
    {
      return  S->Champ2 ;
    }

  Type3_Tssic Struct3_Tssic ( Typestr_Tssic S)
    {
      return  S->Champ3 ;
    }

  Type4_Tssic Struct4_Tssic ( Typestr_Tssic S)
    {
      return  S->Champ4 ;
    }

  void Aff_struct1_Tssic ( Typestr_Tssic S, Type1_Tssic Val )
    {
      strcpy( S->Champ1 , Val );
    }

  void Aff_struct2_Tssic ( Typestr_Tssic S, Type2_Tssic Val )
    {
      strcpy( S->Champ2 , Val );
    }

  void Aff_struct3_Tssic ( Typestr_Tssic S, Type3_Tssic Val )
    {
       S->Champ3 = Val ;
    }

  void Aff_struct4_Tssic ( Typestr_Tssic S, Type4_Tssic Val )
    {
      strcpy( S->Champ4 , Val );
    }


  /** Arbres de recherche binaire **/

  typedef Typestr_Tssic Typeelem_ATssic   ;
  typedef struct Noeud_ATssic * Pointeur_ATssic ;

  struct Noeud_ATssic
    {
      Typeelem_ATssic  Val ;
      Pointeur_ATssic Fg ;
      Pointeur_ATssic Fd ;
      Pointeur_ATssic Pere ;
     } ;

  Typeelem_ATssic Info_ATssic( Pointeur_ATssic P )
    { return P->Val;   }

  Pointeur_ATssic Fg_ATssic( Pointeur_ATssic P)
    { return P->Fg ; }

  Pointeur_ATssic Fd_ATssic( Pointeur_ATssic P)
    { return P->Fd ; }

  Pointeur_ATssic Pere_ATssic( Pointeur_ATssic P)
    { return P->Pere ; }

  void Aff_info_ATssic ( Pointeur_ATssic P, Typeelem_ATssic Val)
    {
      Typeelem_ATssic _Temp ;
      _Temp = malloc(sizeof(Type_Tssic));
      _Temp->Champ1 = malloc(255 * sizeof(char));
      _Temp->Champ2 = malloc(255 * sizeof(char));
      _Temp->Champ4 = malloc(2 * sizeof(char));
      /* Affectation globale de structure */
      strcpy(_Temp->Champ1, Val->Champ1);
      strcpy(_Temp->Champ2, Val->Champ2);
      _Temp->Champ3 = Val->Champ3;
      strcpy(_Temp->Champ4, Val->Champ4);
      Val = _Temp ;
       P->Val = Val ;
    }

  void Aff_fg_ATssic( Pointeur_ATssic P, Pointeur_ATssic Q)
    { P->Fg =  Q;  }

  void Aff_fd_ATssic( Pointeur_ATssic P, Pointeur_ATssic Q)
    { P->Fd =  Q ; }

  void Aff_pere_ATssic( Pointeur_ATssic P, Pointeur_ATssic Q)
    { P->Pere =  Q ; }

  void Creernoeud_ATssic( Pointeur_ATssic *P)
    {
      *P = (struct Noeud_ATssic *) malloc( sizeof( struct Noeud_ATssic))   ;
      (*P)->Val = malloc(sizeof(Type_Tssic));
      (*P)->Val->Champ1 = malloc( 255 * sizeof(char));
      (*P)->Val->Champ2 = malloc( 255 * sizeof(char));
      (*P)->Val->Champ4 = malloc( 2 * sizeof(char));
      (*P)->Fg = NULL;
      (*P)->Fd = NULL;
      (*P)->Pere = NULL;
    }

  void Liberernoeud_ATssic( Pointeur_ATssic P)
    { free( P ) ; }


  /** Tableaux **/

  typedef Pointeur_ATssic Typeelem_V10ATssic ;
  typedef Typeelem_V10ATssic * Typevect_V10ATssic ;

  Typeelem_V10ATssic Element_V10ATssic ( Typevect_V10ATssic V , int I1  )
    {
      return  *(V + I1-1 ) ;
    }

  void Aff_element_V10ATssic ( Typevect_V10ATssic V  , int I1 ,  Typeelem_V10ATssic Val )
    {
      *(V + I1-1 ) = Val ;
    }


  /** Implémentation **\: ARBRE BINAIRE DE STRUCTURES**/

  /** Structures statiques **/

  typedef struct Tiic Type_Tiic  ;
  typedef Type_Tiic * Typestr_Tiic ;
  typedef int Type1_Tiic  ;
  typedef int Type2_Tiic  ;
  typedef string2 Type3_Tiic  ;
  struct Tiic
    {
      Type1_Tiic Champ1 ;
      Type2_Tiic Champ2 ;
      Type3_Tiic Champ3 ;
    };

  Type1_Tiic Struct1_Tiic ( Typestr_Tiic S)
    {
      return  S->Champ1 ;
    }

  Type2_Tiic Struct2_Tiic ( Typestr_Tiic S)
    {
      return  S->Champ2 ;
    }

  Type3_Tiic Struct3_Tiic ( Typestr_Tiic S)
    {
      return  S->Champ3 ;
    }

  void Aff_struct1_Tiic ( Typestr_Tiic S, Type1_Tiic Val )
    {
       S->Champ1 = Val ;
    }

  void Aff_struct2_Tiic ( Typestr_Tiic S, Type2_Tiic Val )
    {
       S->Champ2 = Val ;
    }

  void Aff_struct3_Tiic ( Typestr_Tiic S, Type3_Tiic Val )
    {
      strcpy( S->Champ3 , Val );
    }


  /** Arbres de recherche binaire **/

  typedef Typestr_Tiic Typeelem_ATiic   ;
  typedef struct Noeud_ATiic * Pointeur_ATiic ;

  struct Noeud_ATiic
    {
      Typeelem_ATiic  Val ;
      Pointeur_ATiic Fg ;
      Pointeur_ATiic Fd ;
      Pointeur_ATiic Pere ;
     } ;

  Typeelem_ATiic Info_ATiic( Pointeur_ATiic P )
    { return P->Val;   }

  Pointeur_ATiic Fg_ATiic( Pointeur_ATiic P)
    { return P->Fg ; }

  Pointeur_ATiic Fd_ATiic( Pointeur_ATiic P)
    { return P->Fd ; }

  Pointeur_ATiic Pere_ATiic( Pointeur_ATiic P)
    { return P->Pere ; }

  void Aff_info_ATiic ( Pointeur_ATiic P, Typeelem_ATiic Val)
    {
      Typeelem_ATiic _Temp ;
      _Temp = malloc(sizeof(Type_Tiic));
      _Temp->Champ3 = malloc(2 * sizeof(char));
      /* Affectation globale de structure */
      _Temp->Champ1 = Val->Champ1;
      _Temp->Champ2 = Val->Champ2;
      strcpy(_Temp->Champ3, Val->Champ3);
      Val = _Temp ;
       P->Val = Val ;
    }

  void Aff_fg_ATiic( Pointeur_ATiic P, Pointeur_ATiic Q)
    { P->Fg =  Q;  }

  void Aff_fd_ATiic( Pointeur_ATiic P, Pointeur_ATiic Q)
    { P->Fd =  Q ; }

  void Aff_pere_ATiic( Pointeur_ATiic P, Pointeur_ATiic Q)
    { P->Pere =  Q ; }

  void Creernoeud_ATiic( Pointeur_ATiic *P)
    {
      *P = (struct Noeud_ATiic *) malloc( sizeof( struct Noeud_ATiic))   ;
      (*P)->Val = malloc(sizeof(Type_Tiic));
      (*P)->Val->Champ3 = malloc( 2 * sizeof(char));
      (*P)->Fg = NULL;
      (*P)->Fd = NULL;
      (*P)->Pere = NULL;
    }

  void Liberernoeud_ATiic( Pointeur_ATiic P)
    { free( P ) ; }


  /** Implémentation **\: TABLEAU DE STRUCTURES**/

  /** Tableaux **/

  typedef Typestr_Tssic Typeelem_V210Tssic ;
  typedef Typeelem_V210Tssic * Typevect_V210Tssic ;

  Typeelem_V210Tssic Element_V210Tssic ( Typevect_V210Tssic V , int I1  )
    {
      return  *(V + I1-1 ) ;
    }

  void Aff_element_V210Tssic ( Typevect_V210Tssic V  , int I1 ,  Typeelem_V210Tssic Val )
    {
      Typeelem_V210Tssic _Temp ;
      _Temp = malloc(sizeof(Type_Tssic));
      _Temp->Champ1 = malloc(255 * sizeof(char));
      _Temp->Champ2 = malloc(255 * sizeof(char));
      _Temp->Champ4 = malloc(2 * sizeof(char));
      /* Affectation globale de structure */
      strcpy(_Temp->Champ1, Val->Champ1);
      strcpy(_Temp->Champ2, Val->Champ2);
      _Temp->Champ3 = Val->Champ3;
      strcpy(_Temp->Champ4, Val->Champ4);
      Val = _Temp ;
      *(V + I1-1 ) = Val ;
    }


  /** Implémentation **\: TABLEAU DE STRUCTURES**/

  /** Tableaux **/

  typedef Typestr_Tssic Typeelem_V21Tssic ;
  typedef Typeelem_V21Tssic * Typevect_V21Tssic ;

  Typeelem_V21Tssic Element_V21Tssic ( Typevect_V21Tssic V , int I1  )
    {
      return  *(V + I1-1 ) ;
    }

  void Aff_element_V21Tssic ( Typevect_V21Tssic V  , int I1 ,  Typeelem_V21Tssic Val )
    {
      Typeelem_V21Tssic _Temp ;
      _Temp = malloc(sizeof(Type_Tssic));
      _Temp->Champ1 = malloc(255 * sizeof(char));
      _Temp->Champ2 = malloc(255 * sizeof(char));
      _Temp->Champ4 = malloc(2 * sizeof(char));
      /* Affectation globale de structure */
      strcpy(_Temp->Champ1, Val->Champ1);
      strcpy(_Temp->Champ2, Val->Champ2);
      _Temp->Champ3 = Val->Champ3;
      strcpy(_Temp->Champ4, Val->Champ4);
      Val = _Temp ;
      *(V + I1-1 ) = Val ;
    }


    //    Tableau (1000) de (chaine , chaine , entier , car)
   typedef Typestr_Tssic Typeelem_V100000Tssic ;
  typedef Typeelem_V100000Tssic * Typevect_V100000Tssic ;

  Typeelem_V100000Tssic Element_V100000Tssic ( Typevect_V100000Tssic V , int I1  )
    {
      return  *(V + I1-1 ) ;
    }

  void Aff_element_V100000Tssic ( Typevect_V100000Tssic V  , int I1 ,  Typeelem_V100000Tssic Val )
    {
      Typeelem_V100000Tssic _Temp ;
      _Temp = malloc(sizeof(Type_Tssic));
      _Temp->Champ1 = malloc(255 * sizeof(char));
      _Temp->Champ2 = malloc(255 * sizeof(char));
      _Temp->Champ4 = malloc(2 * sizeof(char));
      /* Affectation globale de structure */
      strcpy(_Temp->Champ1, Val->Champ1);
      strcpy(_Temp->Champ2, Val->Champ2);
      _Temp->Champ3 = Val->Champ3;
      strcpy(_Temp->Champ4, Val->Champ4);
      Val = _Temp ;
      *(V + I1-1 ) = Val ;
    }

  /** Variables du programme principal **/
  Typevect_V10ATssic V ;
  Typevect_V10ATssic S ;
  Pointeur_ATssic A;
  Pointeur_ATiic B;
  Typevect_V210Tssic F,D;
  Typestr_Tiic Perso;
  Typestr_Tssic Personne;
  float K;
  int Tai;
  string2 Cr;
  int _Px1;
  int _Px2;
  int _Px3;
  int _Izw;
  int TAILLE;  /** Variable de contrôle **/

  /** Fonctions standards **/

  int Aleanombre( int N )
    { return ( rand() % N ); }

  char  *Aleachaine ( int N )
    {
      int k;
      char  * Chaine = malloc(N+1);

      char Chr1[26] = "abcdefghijklmnopqrstuvwxyz";
      char Chr2[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

      for (k=0;k<N; k++)
        switch ( rand() % 2 ){
        case 0 :  *(Chaine+k) = Chr1[rand() % 26] ; break ;
        case 1 :  *(Chaine+k) = Chr2[rand() % 26] ; break ;
        }
      Chaine[k] =  '\0' ;

      return (Chaine);
    }


  /** Prototypes des fonctions **/

  string2  Aleares (int *H) ;
  void Inserarb (Pointeur_ATssic *T , Pointeur_ATssic *W , string255 *Nom , string255 *Pre , int *Age , string2 *Res);
  void Creerarb (Pointeur_ATssic *T , int *Z);
  void Afficharb (Pointeur_ATssic *T);
  void Affich_tableau (Typevect_V10ATssic *V , int *Tai);
  void Affich_glob (Pointeur_ATiic *T);
  void Creertab (Typevect_V10ATssic *V , int *Tai);
  void Inser_glob (Pointeur_ATiic *T , Pointeur_ATiic *W , int *Age , int *Occ , string2 *Res);
  void Creer_glob (Pointeur_ATiic *T , Typevect_V210Tssic *F , int *Tai);
  bool  Rech (Pointeur_ATssic *R , int *Ag , string2 *Re , bool *Trouv) ;
  int  Occarb (Typevect_V10ATssic *V , int *Age , string2 *Res) ;
  void Aff_tableau (Pointeur_ATssic *T , Typevect_V210Tssic *V , int *I);
  void Aff_tab_g (Typevect_V10ATssic *V , Typevect_V210Tssic *W , int *Z);
  float  Prctg_arb (Typevect_V210Tssic *F , string2 *Res , int *Mini , int *Maxi , int *Tai) ;
  float Calcul_prctg (int *Nb , int *Nbtotal) ;
  int  Nbtot (Typevect_V210Tssic *F , string2 *Re , int *Tai) ;

  /*-----------------------------*/
  string2  Aleares (int *H) //Fonction qui génere un caractere aleatoirement ('D' ou 'R')
    {
      /** Variables locales **/
      string2  Aleares2 ;
      int T;
      string2 C;

      /** Corps du module **/
     C = malloc(2 * sizeof(char));
     Aleares2 = malloc(2 * sizeof(char));
     T  =  Aleanombre(2 ) ;
     if( T == 0) {
       strcpy (C,   "D") ;
       }
     else
       {
       strcpy (C,   "R") ;

     } ;
     strcpy (Aleares2,   C) ;

     return Aleares2 ;
    }
  /*------------------------------*/
  void Inserarb (Pointeur_ATssic *T , Pointeur_ATssic *W , string255 *Nom , string255 *Pre , int *Age , string2 *Res) //insertion dans l'arbre de la premiere structure
    {
      /** Variables locales **/
      Typestr_Tssic Personne;
      Pointeur_ATssic _Px1;
      Pointeur_ATssic _Px2;

      /** Corps du module **/
     Personne = malloc(sizeof(Type_Tssic));
     Personne->Champ1 = malloc(255 * sizeof(char));
     Personne->Champ2 = malloc(255 * sizeof(char));
     Personne->Champ4 = malloc(2 * sizeof(char));
     if( *T == NULL) {
       Creernoeud_ATssic (& *T ) ;
       Aff_struct1_Tssic ( Personne  , *Nom ) ;
       Aff_struct2_Tssic ( Personne  , *Pre ) ;
       Aff_struct3_Tssic ( Personne  , *Age ) ;
       Aff_struct4_Tssic ( Personne  , *Res ) ;
       Aff_info_ATssic ( *T , Personne ) ;
       Aff_fg_ATssic ( *T , NULL ) ;
       Aff_fd_ATssic ( *T , NULL ) ;
       *W  =  *T ;
       }
     else
       {
       *W  =  NULL ;
      /* Affectation globale de structure */
       strcpy(Personne->Champ1,   Info_ATssic ( *T )->Champ1);
       strcpy(Personne->Champ2,   Info_ATssic ( *T )->Champ2);
       Personne->Champ3 =   Info_ATssic ( *T )->Champ3;
       strcpy(Personne->Champ4,   Info_ATssic ( *T )->Champ4);
 ;
       if( *Age <= Struct3_Tssic ( Personne  )) {
         _Px1 =  Fg_ATssic ( *T ) ;
         Inserarb ( &_Px1, & *W , & *Nom , & *Pre , & *Age , & *Res ) ;
         if( Fg_ATssic ( *T ) == NULL) {
           Aff_fg_ATssic ( *T , *W ) ;

         } ;

       } ;
       if( *Age > Struct3_Tssic ( Personne  )) {
         _Px2 =  Fd_ATssic ( *T ) ;
         Inserarb ( &_Px2, & *W , & *Nom , & *Pre , & *Age , & *Res ) ;
         if( Fd_ATssic ( *T ) == NULL) {
           Aff_fd_ATssic ( *T , *W ) ;

         } ;

       } ;

     } ;

    }
  void Creerarb (Pointeur_ATssic *T , int *Z) //Création d'un seul arbre (pays) avec nombre de noeuds aleatoire
    {
      /** Variables locales **/
      Typevect_V21Tssic V;
      Pointeur_ATssic R;
      int Choix;
      int Age;
      int X;
      string255 Name;
      string255 Fname;
      string2 Result;
      Typestr_Tssic Personne;
      int _Izw;  /** Variable de contrôle **/

      /** Corps du module **/
     V = malloc(20 * sizeof(Typestr_Tssic));
     int _Izw2;for (_Izw2=0; _Izw2<20; ++_Izw2)
       V[_Izw2] = malloc( sizeof(Type_Tssic ));
     int _Izw3;for (_Izw3=0; _Izw3<20; ++_Izw3){
       V[_Izw3]->Champ4= malloc(2 * sizeof(char));}
     Name = malloc(255 * sizeof(char));
     Fname = malloc(255 * sizeof(char));
     Result = malloc(2 * sizeof(char));
     Personne = malloc(sizeof(Type_Tssic));
     Personne->Champ1 = malloc(255 * sizeof(char));
     Personne->Champ2 = malloc(255 * sizeof(char));
     Personne->Champ4 = malloc(2 * sizeof(char));
     if( *Z > 0) {
       for( X  =  1 ;X <=  *Z ; ++X){
         Aff_struct1_Tssic ( Personne  , Aleachaine(Aleanombre(5 ) + 5 ) ) ;
         Aff_struct2_Tssic ( Personne  , Aleachaine(Aleanombre(5 ) + 5 ) ) ;
         Aff_struct3_Tssic ( Personne  , Aleanombre(100 ) + 1 ) ;
         Aff_struct4_Tssic ( Personne  , Aleares ( & Choix ) ) ;
         Aff_element_V21Tssic ( V , X   , Personne ) ;
         strcpy (Name,   Struct1_Tssic ( Element_V21Tssic ( V , X   )  )) ;
         strcpy (Fname,   Struct2_Tssic ( Element_V21Tssic ( V , X   )  )) ;
         Age  =  Struct3_Tssic ( Element_V21Tssic ( V , X   )  ) ;
         strcpy (Result,   Struct4_Tssic ( Element_V21Tssic ( V , X   )  )) ;
         Inserarb ( & *T , & R , & Name , & Fname , & Age , & Result ) ;

       } ;

     } ;

    }
   void Afficharb (Pointeur_ATssic *T) //Affiche un seul arbre (pays) en inordre (trié)
    {
      /** Variables locales **/
      Pointeur_ATssic _Px1;
      Pointeur_ATssic _Px2;

      /** Corps du module **/
     if( *T != NULL) {
       _Px1 =  Fg_ATssic ( *T ) ;
       Afficharb ( &_Px1) ;
       printf ( " \n%s\n", "Nom :" ) ;
       printf ( " %s\n", Struct1_Tssic(Info_ATssic(*T)) ) ;
       printf ( " %s\n", "Prénom :" ) ;
       printf ( " %s\n", Struct2_Tssic(Info_ATssic(*T)) ) ;
       printf ( " %s\n", "Age :" ) ;
       printf ( " %d\n", Struct3_Tssic(Info_ATssic(*T)) ) ;
       printf ( " %s\n", "Résultat :" ) ;
       printf ( " %s\n", Struct4_Tssic(Info_ATssic(*T)) ) ;
       printf ( " %s\n", "****************" ) ;
       char a = getchar();
       _Px2 =  Fd_ATssic ( *T ) ;
       Afficharb ( &_Px2) ;

     };

    }
  void Affich_glob (Pointeur_ATiic *T) //affiche un seul arbre de la deuxieme structure
    {
      /** Variables locales **/
      Pointeur_ATiic _Px1;
      Pointeur_ATiic _Px2;

      /** Corps du module **/
     if( *T != NULL) {
       _Px1 =  Fg_ATiic ( *T ) ;
       Affich_glob ( &_Px1) ;
       printf ( " %s\n", "Age :" ) ;
       printf ( " %d\n", Struct1_Tiic(Info_ATiic(*T)) ) ;
       printf ( " %s\n", "Occurence :" ) ;
       printf ( " %d\n", Struct2_Tiic(Info_ATiic(*T)) ) ;
       printf ( " %s\n", "Résultat :" ) ;
       printf ( " %s\n", Struct3_Tiic(Info_ATiic(*T)) ) ;
       printf ( " %s\n", "****************" ) ;
       char a = getchar();
       _Px2 =  Fd_ATiic ( *T ) ;
       Affich_glob ( &_Px2) ;

     } ;

    }
  void Creertab (Typevect_V10ATssic *V , int *Tai) //Cree le tableau de 10 pays dans chaque case un arbre (un pays)
    {
      /** Variables locales **/
      Pointeur_ATssic A;
      int I;
      int _Px1;

      /** Corps du module **/
     I  =  1 ;
     for( I  =  1 ;I <=  *Tai ; ++I){
       _Px1 =  Aleanombre(21 ) + 1 ;
       A=NULL;
       Creerarb ( & A , &_Px1) ;
       Aff_element_V10ATssic ( *V , I   , A ) ;
       A  =  NULL ;

     } ;

    }

    void Affich_tableau (Typevect_V10ATssic *V , int *Tai) //Affiche le tableau de 10 pays
    {
      /** Variables locales **/
      int J;
      Pointeur_ATssic _Px1;

      /** Corps du module **/
     J  =  1 ;
     for( J  =  1 ;J <=  *Tai ; ++J){
        textcolor(15);
        textbackground(0);
        printf("                                                    <<  LE PAYS  %d  >>                                                  ",J);
         textcolor(0);
        textbackground(15);
       _Px1 =  Element_V10ATssic ( *V , J   ) ;
       Afficharb ( &_Px1) ;
       char a = getchar();
     } ;

    }
  void Inser_glob (Pointeur_ATiic *T , Pointeur_ATiic *W , int *Age , int *Occ , string2 *Res) //insertion dans l'arbre de la deuxieme structure
    {
      /** Variables locales **/
      Typestr_Tiic Perso;
      Pointeur_ATiic _Px1;
      Pointeur_ATiic _Px2;
      Pointeur_ATiic _Px3;
      Pointeur_ATiic _Px4;

      /** Corps du module **/
     Perso = malloc(sizeof(Type_Tiic));
     Perso->Champ3 = malloc(2 * sizeof(char));
     if( *T == NULL) {
       Creernoeud_ATiic (& *T ) ;
       Aff_struct1_Tiic ( Perso  , *Age ) ;
       Aff_struct2_Tiic ( Perso  , *Occ ) ;
       Aff_struct3_Tiic ( Perso  , *Res ) ;
       Aff_info_ATiic ( *T , Perso ) ;
       Aff_fg_ATiic ( *T , NULL ) ;
       Aff_fd_ATiic ( *T , NULL ) ;
       *W  =  *T ;
       }
     else
       {
       *W  =  NULL ;
       if( ( *Age < Struct1_Tiic ( Info_ATiic ( *T )  ) ) && (strcmp( Struct3_Tiic ( Info_ATiic ( *T )  ), "R") == 0  )) {
         _Px1 =  Fg_ATiic ( *T ) ;
         Inser_glob ( &_Px1, & *W , & *Age , & *Occ , & *Res ) ;
         if( Fg_ATiic ( *T ) == NULL) {
           Aff_fg_ATiic ( *T , *W ) ;

         } ;

       } ;
       if( ( *Age > Struct1_Tiic ( Info_ATiic ( *T )  ) ) && (strcmp( Struct3_Tiic ( Info_ATiic ( *T )  ), "D") == 0  )) {
         _Px2 =  Fd_ATiic ( *T ) ;
         Inser_glob ( &_Px2, & *W , & *Age , & *Occ , & *Res ) ;
         if( Fd_ATiic ( *T ) == NULL) {
           Aff_fd_ATiic ( *T , *W ) ;

         } ;

       } ;
       if( ( *Age > Struct1_Tiic ( Info_ATiic ( *T )  ) ) && (strcmp( Struct3_Tiic ( Info_ATiic ( *T )  ), "R") == 0  )) {
         _Px3 =  Fd_ATiic ( *T ) ;
         Inser_glob ( &_Px3, & *W , & *Age , & *Occ , & *Res ) ;
         if( Fd_ATiic ( *T ) == NULL) {
           Aff_fd_ATiic ( *T , *W ) ;

         } ;

       } ;
       if( ( *Age < Struct1_Tiic ( Info_ATiic ( *T )  ) ) && (strcmp( Struct3_Tiic ( Info_ATiic ( *T )  ), "D") == 0  )) {
         _Px4 =  Fg_ATiic ( *T ) ;
         Inser_glob ( &_Px4, & *W , & *Age , & *Occ , & *Res ) ;
         if( Fg_ATiic ( *T ) == NULL) {
           Aff_fg_ATiic ( *T , *W ) ;

         } ;

       } ;

     } ;

    }
  void Creer_glob (Pointeur_ATiic *T , Typevect_V210Tssic *F , int *Tai)//Creation de l'arbre de la deuxieme structure
    {
      /** Variables locales **/
      Pointeur_ATiic R;
      int X;
      int Ag;
      int Oc;
      string2 Re;

      /** Corps du module **/
     Re = malloc(2 * sizeof(char));
     for( X  =  1 ;X <=  *Tai - 1 ; ++X){
       Ag  =  Struct3_Tssic ( Element_V210Tssic ( *F , X   )  ) ;
       strcpy (Re,   Struct4_Tssic ( Element_V210Tssic ( *F , X   )  )) ;
       Oc  =  Occarb ( & V , & Ag , & Re ) ;
    if (Oc==0)
    Oc=Oc;

       Inser_glob ( & *T , & R , & Ag , & Oc , & Re ) ;

     } ;

    }
  /* Dans un seul arbre */

  bool  Rech (Pointeur_ATssic *R , int *Ag , string2 *Re , bool *Trouv) //retourne vrai si trouve la personne avec l'age Ag et le resultat Re
    {
      /** Variables locales **/
      bool  Rech2 ;
      Pointeur_ATssic _Px1;
      Pointeur_ATssic _Px2;
      Pointeur_ATssic _Px3;
      Pointeur_ATssic _Px4;

      /** Corps du module **/
     if( ( *R == NULL )) {
       *Trouv  =  False ;
       }
     else
       {
       if( ( *Ag == Struct3_Tssic ( Info_ATssic ( *R )  ) ) && (strcmp( *Re, Struct4_Tssic ( Info_ATssic ( *R )  )) == 0  )) {
         *Trouv  =  True ;
         }
       else
         {
         if( (strcmp( *Re, "D") == 0  ) && ( *Ag < Struct3_Tssic ( Info_ATssic ( *R )  ) )) {
           _Px1 =  Fg_ATssic ( *R ) ;
           Rech2  =  Rech ( &_Px1, & *Ag , & *Re , & *Trouv ) ;

         } ;
         if( (strcmp( *Re, "R") == 0  ) && ( *Ag > Struct3_Tssic ( Info_ATssic ( *R )  ) )) {
           _Px2 =  Fd_ATssic ( *R ) ;
           Rech2  =  Rech ( &_Px2, & *Ag , & *Re , & *Trouv ) ;

         } ;
         if( (strcmp( *Re, "R") == 0  ) && ( *Ag < Struct3_Tssic ( Info_ATssic ( *R )  ) )) {
           _Px3 =  Fg_ATssic ( *R ) ;
           Rech2  =  Rech ( &_Px3, & *Ag , & *Re , & *Trouv ) ;

         } ;
         if( (strcmp( *Re, "D") == 0  ) && ( *Ag > Struct3_Tssic ( Info_ATssic ( *R )  ) )) {
           _Px4 =  Fd_ATssic ( *R ) ;
           Rech2  =  Rech ( &_Px4, & *Ag , & *Re , & *Trouv ) ;

         } ;

       } ;

     } ;
     Rech2  =  *Trouv ;

     return Rech2 ;
    }
  /* TOUTS LES PAYS */

  int  Occarb (Typevect_V10ATssic *V , int *Age , string2 *Res) // Retourne nombre d'occurence De la personne avec l'age Age et le resultat Res dnas tous les pays
    {
      /** Variables locales **/
      int  Occarb2 ;
      Pointeur_ATssic A;
      int Occu;
      int Q;
      bool Trouv;
      Pointeur_ATssic _Px1;

      /** Corps du module **/
     Occu  =  0 ;
     for( Q  =  1 ;Q <=  10 ; ++Q){
       Trouv  =  False ;
       _Px1 =  Element_V10ATssic ( *V , Q   ) ;
       if( Rech ( &_Px1, & *Age , & *Res , & Trouv ) == True) {
         ;
         Occu  =  Occu + 1 ;

       } ;

     } ;
     Occarb2  =  Occu ;

     return Occarb2 ;
    }


  void Aff_tableau (Pointeur_ATssic *T , Typevect_V210Tssic *V , int *I) // remplir un vecteur depuis un arbre
    {
      /** Variables locales **/
      Pointeur_ATssic _Px1;
      Pointeur_ATssic _Px2;

      /** Corps du module **/
     if( *T != NULL) {
       _Px1 =  Fg_ATssic ( *T ) ;
       Aff_tableau ( &_Px1, & *V , & *I ) ;
       Aff_element_V210Tssic ( *V , *I   , Info_ATssic ( *T ) ) ;
       *I  =  *I + 1 ;
       _Px2 =  Fd_ATssic ( *T ) ;
       Aff_tableau ( &_Px2, & *V , & *I ) ;

     } ;

    }


  void Aff_tab_g (Typevect_V10ATssic *V , Typevect_V210Tssic *W , int *Z)// Remplir tous les pays dans un vecteur
    {
      /** Variables locales **/
      int I;
      int J;
      Pointeur_ATssic _Px1;

      /** Corps du module **/
     J  =  1 ;
     for( I  =  1 ;I <=  10 ; ++I){
       _Px1 =  Element_V10ATssic ( *V , I   ) ;
       Aff_tableau ( &_Px1, & *W , & J ) ;

     } ;
     *Z  =  J ;

    }
  float  Prctg_arb (Typevect_V210Tssic *F , string2 *Res , int *Mini , int *Maxi , int *Tai) //Retourne le pourcentage de Resultat "Res" entre l'age Mini et Maxi dans tous les pays
    {
      /** Variables locales **/
      float  Prctg_arb2 ;
      int Som;
      int H;
      int Total;

      /** Corps du module **/
     Som  =  0 ;
     for( H  =  1 ;H <=  *Tai - 1 ; ++H){
       if( ( Struct3_Tssic ( Element_V210Tssic ( *F , H   )  ) <= *Maxi ) && ( Struct3_Tssic ( Element_V210Tssic ( *F , H   )  ) >= *Mini )) {
         if(strcmp( Struct4_Tssic ( Element_V210Tssic ( *F , H   )  ), *Res) == 0 ) {
           Som  =  Som + 1 ;

         } ;

       } ;

     } ;
     Total  =  Nbtot ( & *F , & *Res , & *Tai ) ;
     Prctg_arb2  =  Calcul_prctg ( & Som , & Total ) ;

     return Prctg_arb2 ;
    }
  float Calcul_prctg (int *Nb , int *Nbtotal)// calcul pourcnetage de Nb tel que le nombre total est Nbtotal
    {
      /** Variables locales **/
      float  Calcul_prctg2 ;
      float Calc;

      /** Corps du module **/
     Calc  =  0 ;
     if( *Nbtotal != 0) {
       Calc  =  *Nb * 100 ;
       Calc  =  ( Calc / (float) *Nbtotal ) ;
       Calcul_prctg2  =  Calc ;

     } ;
     return Calcul_prctg2;
    }
  int  Nbtot (Typevect_V210Tssic *F , string2 *Re , int *Tai)//retourne le nombre total de resultat "Re" dans tous les pays
    {
      /** Variables locales **/
      int  Nbtot2 ;
      int J;
      int Nb;

      /** Corps du module **/
     Nb  =  0 ;
     for( J  =  1 ;J <=  *Tai - 1 ; ++J){
       if(strcmp( Struct4_Tssic ( Element_V210Tssic ( *F , J   )  ), *Re) == 0 ) {
         Nb  =  Nb + 1 ;

       } ;

     } ;
     Nbtot2  =  Nb ;

     return Nbtot2 ;
    }








      void Inser_Pays_C (Pointeur_ATssic *TC , Pointeur_ATssic *WC , string255 *NomC , string255 *PreC , int *AgeC , string2 *ResC) //insertion dans l'arbre de la structure de partie c
    {
      /** Variables locales **/
      //int P;
      Typestr_Tssic Personne;
      Pointeur_ATssic _Px1;
      Pointeur_ATssic _Px2;


      /** Corps du module **/
     Personne = malloc(sizeof(Type_Tssic));
     Personne->Champ1 = malloc(255 * sizeof(char));
     Personne->Champ2 = malloc(255 * sizeof(char));
     Personne->Champ4 = malloc(2 * sizeof(char));
     if( *TC == NULL) {
       Creernoeud_ATssic (& *TC ) ;
       Aff_struct1_Tssic ( Personne  , *NomC ) ;
       Aff_struct2_Tssic ( Personne  , *PreC) ;
       Aff_struct3_Tssic ( Personne  , *AgeC ) ;
       Aff_struct4_Tssic ( Personne  , *ResC ) ;
       Aff_info_ATssic ( *TC , Personne ) ;
       Aff_fg_ATssic ( *TC , NULL ) ;
       Aff_fd_ATssic ( *TC , NULL ) ;
       *WC  =  *TC ;
       }
     else
       {
       *WC  =  NULL ;
        /* Affectation globale de structure */
       strcpy(Personne->Champ1,   Info_ATssic ( *TC )->Champ1);
       strcpy(Personne->Champ2,   Info_ATssic ( *TC )->Champ2);
       Personne->Champ3 =   Info_ATssic ( *TC )->Champ3;
       strcpy(Personne->Champ4,   Info_ATssic ( *TC )->Champ4);

       if( *AgeC <= Struct3_Tssic ( Personne  )) {
         _Px1 =  Fg_ATssic ( *TC ) ;
         Inser_Pays_C ( &_Px1, & *WC , & *NomC , & *PreC , & *AgeC , & *ResC ) ;
         if( Fg_ATssic ( *TC ) == NULL) {
           Aff_fg_ATssic ( *TC , *WC ) ;
         }
         };



       if( *AgeC > Struct3_Tssic ( Personne  )) {
         _Px2 =  Fd_ATssic ( *TC ) ;
         Inser_Pays_C ( &_Px2, & *WC , & *NomC , & *PreC , & *AgeC , & *ResC ) ;
         if( Fd_ATssic ( *TC ) == NULL) {
           Aff_fd_ATssic ( *TC , *WC ) ;

         }

       } ;

     } ;

    }
         void prctg_pays (int *nombreD , int *nombreR )//retourne le pourcentage des morts et des guéris dans un pays de fichier.txt
  {
      if (*nombreD > *nombreR)
      {
        *nombreD = ( *nombreD * 100 ) / ( *nombreD + *nombreR );
        *nombreR = ( 100  - *nombreD );
      }
      else
      {
        *nombreR = ( *nombreR * 100 ) / ( *nombreR + *nombreD );
        *nombreD = ( 100 - *nombreR);
      }
  }



void extraire_ligne (const char* name , int line , char tab[])//fait l'extrait d'une ligne d'un fichier
{
char c , buff[50]={0};
int count=1;
FILE *fp = NULL;
fp = fopen (name,"r");
if (fp == NULL)
{
//printf("L'ouverture de fichier est impossible");
exit(0);
}
do
{
c = fgetc((fp));
strncat(buff,&c,1);
if (c =='\n')
{
if (count == line)
strcpy(tab , buff);
memset(buff,0,sizeof(buff));
count++;
}
}while (c!=EOF);
/*if (line > count || line <= 0 )
{
printf("La ligne est vide");
}*/

//return 0;
}



void extraire_ND(char ligne[],char nd[] )//fait l'extrait de nombre des morts d'un fichier
{
    int i=24,j = 0; //i = 24 : la position de premier chiffre de chaque ND dans le fichier
    while((ligne[i] < 58) && (ligne[i] > 47 ))
    {
        nd[j]=ligne[i];
        i++;
        j++;
    }
    nd[j]='\0';
}

void extraire_NR(char ligne[],char nr[])//fait l'extrait de nombre des guéris d'un fichier
{
    int i=48,j=0;//i = 48 : la position de premier chiffre de chaque NR dans le fichier
    while((ligne[i] < 58) && (ligne[i] > 47 ))
    {
        nr[j]=ligne[i];
        i++;
        j++;
    }
    nr[j]='\0';
}

int minimum (int a ,int b )//retourne le plus petit nombre  entre deux entiers
    {
        if ( a > b )
        {
            return b;
        }
        else
        {
            return a;
        }
    }

 void Creer_Pays_C (Pointeur_ATssic *T , int seuil , char ligne[])//creation d'un arbre(pays) de la structure de partie c
    {
      // Variables locales
      Typevect_V21Tssic V;
      Pointeur_ATssic R;
      string2 Nrr;
      string2 Ndd;
      string255 Name;
      string255 Fname;
      string2 Result;
      Typestr_Tssic Personne;
      int Age ,z , NBd , NBr , NBperso , x , y;
      char line [53];
      char nddd [5];
      char nrrr [5];

     int _Izw;  /** Variable de contrôle **/

       /** Corps du module **/

     extraire_ND (ligne ,nddd );
      NBd = atoi(nddd);//convertir la chaine de caracteres des ND vers un entier
     extraire_NR (ligne ,nrrr );
     NBr = atoi(nrrr);//convertir la chaine de caracteres des NR vers un entier
     NBperso = minimum ( seuil , (NBd + NBr) );//donne le minimum entre le seuil choisi(5000) et le nombre réel des guéris et morts dans un pays
     if ( NBperso == seuil )//dans le cas ou le nombre réel des guéris et morts dans un pays est superieur au seuil
     {
         prctg_pays (&NBd , &NBr );
         x = ( NBd * (seuil) ) / 100;
         y = ( NBr * (seuil) ) / 100;
     }
     else //dans le cas ou le nombre réel des guéris et morts dans un pays est inferieur au seuil
     {
         x = NBd;
         y = NBr;
     };


     V = malloc(5000 * sizeof(Typestr_Tssic));
     int _Izw2;for (_Izw2=0; _Izw2<5000; ++_Izw2)
       V[_Izw2] = malloc( sizeof(Type_Tssic ));
     int _Izw3;for (_Izw3=0; _Izw3<5000; ++_Izw3){
       V[_Izw3]->Champ4= malloc(2 * sizeof(char));}
     Name = malloc(255 * sizeof(char));
     Fname = malloc(255 * sizeof(char));
     Result = malloc(2 * sizeof(char));
     Ndd = malloc(2 * sizeof(char));
     Nrr = malloc(2 * sizeof(char));
     Personne = malloc(sizeof(Type_Tssic));
     Personne->Champ1 = malloc(255 * sizeof(char));
     Personne->Champ2 = malloc(255 * sizeof(char));
     Personne->Champ4 = malloc(2 * sizeof(char));

       for( z  =  1 ;z <=  x ; ++z){
       strcpy(Ndd , "D") ;
       Aff_struct1_Tssic ( Personne  , Aleachaine(Aleanombre(5 ) + 5 ) ) ;
       Aff_struct2_Tssic ( Personne  , Aleachaine(Aleanombre(5 ) + 5 ) ) ;
       Aff_struct3_Tssic ( Personne  , Aleanombre(100 ) + 1 )  ;
       Aff_struct4_Tssic ( Personne  , Ndd ) ;
       Aff_element_V21Tssic ( V , z   , Personne ) ;
       strcpy (Name,   Struct1_Tssic ( Element_V21Tssic ( V , z   )  )) ;
       strcpy (Fname,   Struct2_Tssic ( Element_V21Tssic ( V , z   )  )) ;
       Age  =  Struct3_Tssic ( Element_V21Tssic ( V , z   )  ) ;
       strcpy (Result,   Struct4_Tssic ( Element_V21Tssic ( V , z   )  )) ;
       Inser_Pays_C ( & *T , & R , & Name , & Fname , & Age , & Result ) ;
       } ;
       z = x + 1;
              for( z  =  x + 1 ;z <=  x + y ; ++z){
       strcpy(Nrr , "R") ;
       Aff_struct1_Tssic ( Personne  , Aleachaine(Aleanombre(5 ) + 5 ) ) ;
       Aff_struct2_Tssic ( Personne  , Aleachaine(Aleanombre(5 ) + 5 ) ) ;
       Aff_struct3_Tssic ( Personne  , Aleanombre(100 ) + 1 ) ;
       Aff_struct4_Tssic ( Personne  , Nrr ) ;
       Aff_element_V21Tssic ( V , z   , Personne ) ;
       strcpy (Name,   Struct1_Tssic ( Element_V21Tssic ( V , z   )  )) ;
       strcpy (Fname,   Struct2_Tssic ( Element_V21Tssic ( V , z   )  )) ;
       Age  =  Struct3_Tssic ( Element_V21Tssic ( V , z   )  ) ;
       strcpy (Result,   Struct4_Tssic ( Element_V21Tssic ( V , z   )  )) ;
        Inser_Pays_C ( & *T , & R , & Name , & Fname , & Age , & Result ) ;

       } ;

    }

   void Affiche_Pays_C (Pointeur_ATssic *T)//module qui affiche un seul pays de fichier
    {
      /** Variables locales **/
      Pointeur_ATssic _Px1;
      Type_Tssic _Struct_Temp1;
      Pointeur_ATssic _Px2;

      /** Corps du module **/
     if( *T != NULL) {
       _Px1 =  Fg_ATssic ( *T ) ;
       Affiche_Pays_C ( &_Px1) ;
       /** Ecriture d'une structure */
       _Struct_Temp1 = *Info_ATssic(*T);

       printf ( "\nNom : %s\n", _Struct_Temp1.Champ1 );
       printf ( "Prenom : %s\n", _Struct_Temp1.Champ2 );
       printf ( "Age : %d\n", _Struct_Temp1.Champ3 );
       printf ( "Resultat : %s\n", _Struct_Temp1.Champ4 );
       printf ( " %s\n", "****************" ) ;
       _Px2 =  Fd_ATssic ( *T ) ;
       Affiche_Pays_C ( &_Px2) ;

     } ;

    }



     void Creer_Tab_C (  Typevect_V10ATssic   *V , int *Tai )//Creation de tableau des 100 pays
    {
      /** Variables locales **/
      Pointeur_ATssic A;
      int I , pp =500,n = 4;//Le seuil (pp) est pris à 5000
      //n = 4  :  La ligne du prmeier pays d'aprés le fichier.txt
      /** Corps du module **/
     I  =  1 ;
     for( I  =  1 ;I <=  *Tai ; ++I){
       A=NULL;
       char tab [53];
       const char* name = "fichier.txt";
       extraire_ligne(name , n , tab);
       Creer_Pays_C(&A , pp , tab);
       Aff_element_V10ATssic ( *V , I   , A ) ;
       A  =  NULL ;
       n++;

     } ;

    }


   void affichpays (Typevect_V10ATssic   *V , int *Tai)//Module qui permet d'afficher tous les 100 pays
    {
    Pointeur_ATssic _Px1 ;
    int i = 1,j = 2;
    for(i  =  1 ;i <=  *Tai ; ++i)
    {
      textbackground(0);
        textcolor(15);
    printf ( " ********************************************* LE PAYS << %d >> ********************************************* \n", j );
    _Px1 =  Element_V10ATssic ( *V , i  ) ;
        textbackground(15);
        textcolor(0);
    Affiche_Pays_C( &_Px1);

    j ++;
    }
    }





 /*          _______________________________________________________________________________________________________
            |                                                                                                       |
            |                                    _______________________________                                    |
            |                                   |                               |                                   |
            |                                   |       Programme Général       |                                   |
            |                                   |_______________________________|                                   |
            |                                                                                                       |
            |                                                                                                       |
            |_______________________________________________________________________________________________________|                  */




  int main(int argc, char *argv[])
    {
        intro();// module d'acceuil
         deb: //étiquette de début
         basemenu_partie();// affichage menu choix des parties
         textcolor(0);
        textbackground(7);
        printdirection("VEUILLEZ CHOISIR LA PARTIE QUE VOUS VOULLEZ TRAITER :","right",35,18,10);
     V = malloc(10 * sizeof(Pointeur_ATssic));
     int _Izw2;for (_Izw2=0; _Izw2<10; ++_Izw2)
       V[_Izw2] = malloc( sizeof(Pointeur_ATssic ));
     F = malloc(210 * sizeof(Typestr_Tssic));
     int _Izw3;for (_Izw3=0; _Izw3<210; ++_Izw3)
       F[_Izw3] = malloc( sizeof(Type_Tssic ));
     int _Izw4;for (_Izw4=0; _Izw4<210; ++_Izw4){
       F[_Izw4]->Champ4= malloc(2 * sizeof(char));}
     Perso = malloc(sizeof(Type_Tiic));
     Perso->Champ3 = malloc(2 * sizeof(char));
     Personne = malloc(sizeof(Type_Tssic));
     Personne->Champ1 = malloc(255 * sizeof(char));
     Personne->Champ2 = malloc(255 * sizeof(char));
     Personne->Champ4 = malloc(2 * sizeof(char));
     Cr = malloc(2 * sizeof(char));
     _Px1 =  10 ;
     switch (choix_partie()) //menu choix des parties
       {
         case 1:
             menuu1:
                 system("cls");
                 basemenu_1();//affichage menu choix de la partie 1
             switch(choix_1())//menu choix de la partie 1
             {

               case 1:
                   system("cls");
                    textcolor(0);
                    textbackground(7);
                    printdirection("                                             CREATION DE LA PREMIERE STRUCTURE                                         ","right",1,4,5);
                    decalrectangle(3);
                    Creertab ( & V , &_Px1) ;
                    textcolor(15);
                    textbackground(0);
                    printdirection("                      PROGRESSION                     ","right",33,20,0);textbackground(7);
                    printdirection("                                                      ","right",33,21,0);textbackground(7);
                    printdirection("                                                      ","right",33,22,0);textbackground(7);
                    printdirection("                                                      ","right",33,23,0);textbackground(7);
                    printdirection("                                                  ","right",35,22,0);
                    gotoxy(58,22);
                    textcolor(0);
                    printf("FIN");
                    gotoxy(40,30);
                    system("pause");
               break;
               case 2:
                   system("cls");
                   textcolor(0);
                    textbackground(7);
                    printdirection("                                             AFFICHAGE DE LA PREMIERE STRUCTURE                                         ","right",1,4,5);
                 Affich_tableau( & V , &_Px1);
                 system("pause");
               break;
               case 3:
                   system("cls");
                   textcolor(0);
                    textbackground(7);
                    printdirection("                                             CREATION DE LA DEUXIEME STRUCTURE                                          ","right",1,4,5);
                    decalrectangle(3);
                    Aff_tab_g ( & V , & F , & Tai ) ;
                    Creer_glob ( & B , & F , & Tai ) ;
                    textcolor(15);
                    textbackground(0);
                    printdirection("                      PROGRESSION                     ","right",33,20,0);textbackground(7);
                    printdirection("                                                      ","right",33,21,0);textbackground(7);
                    printdirection("                                                      ","right",33,22,0);textbackground(7);
                    printdirection("                                                      ","right",33,23,0);textbackground(7);
                    printdirection("                                                  ","right",35,22,0);
                    gotoxy(58,22);
                    textcolor(0);
                    printf("FIN");
                    gotoxy(40,30);
                    system("pause");
               break;
               case 4:
                   system("cls");
                    textcolor(0);
                    textbackground(7);
                    printdirection("                                             AFFICHAGE DE LA DEUXIEME STRUCTURE                                         ","right",1,4,5);
                 Affich_glob ( & B ) ;
                 system("pause");
               break;
               case 5:
                   system("cls");
                    textcolor(0);
                textbackground(7);
                printdirection("                                                    CALCUL DE POURCENTAGE                                            ","right",1,4,5);
                decalrectangle(3);
                 textcolor(15);
                textbackground(7);
                gotoxy(4,11);
                printf("<> LE R%cSULTAT QUE VOUS VOULLEZ RECHERCHER (D / R)  : ",144);
                textcolor(0);
                textbackground(15);
                gotoxy(65,11);
                scanf ( " %s", Cr ) ;
                textcolor(15);
                textbackground(7);
                gotoxy(4,13);
                printf("<> LA BORNE MINIMALE DE L'AGE  : ");
                textcolor(0);
                textbackground(15);
                gotoxy(65,13);
                scanf ( "%d", &_Px2 ) ;
                textcolor(15);
                textbackground(7);
                gotoxy(4,15);
                printf("<> LA BORNE MAXIMALE DE L'AGE  : ");
                textcolor(0);
                textbackground(15);
                gotoxy(65,15);
                scanf ( "%d", &_Px3 ) ;
                 K  =  Prctg_arb ( & F , & Cr , &_Px2, &_Px3, & Tai ) ;
                 gotoxy(45,20);
                textcolor(15);
                textbackground(0);
                 printf ( " %s %f\n", "LE POURCENTAGE EST :",K ) ;
                 gotoxy(40,30);
                  textcolor(0);
                textbackground(15);
                 system("pause");
               break;
               case 6://cas de cliquer sur exit de partie Z
                   goto deb;
                break;
             }
          goto menuu1;
          break;


         case 2:
             menuu2:
            basemenu_2();//affichage menu choix de la partie 2
            switch(choix_2())//menu choix de la partie 2
            {
            case 1://veuillez attendre quelques secondes avant que la creation de la structure se termine .
                system("cls");
            S = malloc(100 * sizeof(Pointeur_ATssic));
            int _Izw2;for (_Izw2=0; _Izw2<100; ++_Izw2)
            S[_Izw2] = malloc( sizeof(Pointeur_ATssic ));
            D = malloc(10000 * sizeof(Pointeur_ATssic));
            int _Izw1;for (_Izw1=0; _Izw1<10000; ++_Izw1)
            D[_Izw1] = malloc( sizeof(Pointeur_ATssic ));
            int j = 100;
            textcolor(0);
                    textbackground(7);
                    printdirection("                                                 CREATION DE LA STRUCTURE                                              ","right",1,4,5);
                    decalrectangle(3);
              Creer_Tab_C(&S , &j);
              textcolor(15);
                    textbackground(0);
                    printdirection("                      PROGRESSION                     ","right",33,20,0);textbackground(7);
                    printdirection("                                                      ","right",33,21,0);textbackground(7);
                    printdirection("                                                      ","right",33,22,0);textbackground(7);
                    printdirection("                                                      ","right",33,23,0);textbackground(7);
                    printdirection("                                                  ","right",35,22,0);
                    gotoxy(58,22);
                    textcolor(0);
                    printf("FIN");
                    gotoxy(40,30);
                    system("pause");
            break;
            case 2:
                system("cls");
                textcolor(0);
                textbackground(7);
                printdirection("                                                  AFFICHAGE DE LA STRUCTURE                                             ","right",1,4,5);
                 Aff_tab_g ( & V , & D , & Tai ) ;
                 //Creer_glob ( & B , & D , & Tai) ;
                 //Affich_glob ( & B ) ;
                system("pause");
            break;
            case 3:
                goto deb; // cas de cliquer sur exit de menu partie C
            break;
            }
           goto menuu2;
           break;

          case 3:
                goto fin; // cas de cliquer sur exit (fin du programme)
          break;

             goto deb;

        fin :
        fin(); //affichage de fin de programme

       }
      //return 0;
    }
