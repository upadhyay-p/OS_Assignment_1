#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<termios.h>
#include<sys/ioctl.h>
#include<pwd.h>
#include<grp.h>
#include<iostream>
#include<time.h>
#include<cstring>
#include<stropts.h>
#include<vector>
using namespace std;

#define KEY_ESCAPE  0x001b
#define KEY_ENTER   0x000a
#define KEY_UP      0x0105
#define KEY_DOWN    0x0106
#define KEY_LEFT    0x0107
#define KEY_RIGHT   0x0108
#define COLON       0x003a

static struct termios term, oterm;

static int getch(void);
static int kbhit(void);
static int kbesc(void);
static int kbget(void);
static int getch(void);
extern int cursorloc=0;
int i;
extern vector<string> list;
//extern vector<struct fnode*> list;

void commandMode(){
    
}

void cursorforward(int x){ 
    if(cursorloc>0){
    printf("\033[%dA", (x));
    cursorloc--;
}
}

void cursorbackward(int x) {
    if(cursorloc<i-1){
    printf("\033[%dB", (x));
    cursorloc++;
}
}
/*void gotoxy(int x, int y)
{
printf("\x1b[%d;%dH",(x),(y));
}*/


static int getch(void)
{
    int c = 0;

    tcgetattr(0, &oterm);
    memcpy(&term, &oterm, sizeof(term));
    term.c_lflag &= ~(ICANON | ECHO);
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &term);
    c = getchar();
    tcsetattr(0, TCSANOW, &oterm);
    return c;
}

static int kbhit(void)
{
    int c = 0;

    tcgetattr(0, &oterm);
    memcpy(&term, &oterm, sizeof(term));
    term.c_lflag &= ~(ICANON | ECHO);
    term.c_cc[VMIN] = 0;
    term.c_cc[VTIME] = 1;
    tcsetattr(0, TCSANOW, &term);
    c = getchar();
    tcsetattr(0, TCSANOW, &oterm);
    if (c != -1) ungetc(c, stdin);
    return ((c != -1) ? 1 : 0);
}

static int kbesc(void)
{
    int c;

    if (!kbhit()) return KEY_ESCAPE;
    c = getch();
    if (c == '[') {
        switch (getch()) {
            case 'A':
                c = KEY_UP;
                break;
            case 'B':
                c = KEY_DOWN;
                break;
            case 'C':
                c = KEY_LEFT;
                break;
            case 'D':
                c = KEY_RIGHT;
                break;
            default:
                c = 0;
                break;
        }
    } else {
        c = 0;
    }
    if (c == 0) while (kbhit()) getch();
    return c;
}

static int kbget(void)
{
    int c;

    c = getch();
    if(c==KEY_ESCAPE) kbesc();
    else if(c==COLON) {
        kbhit();
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        printf("\033[%d;%dH Command Mode:", w.ws_row,w.ws_col);
        commandMode();

    }
    //return (c == KEY_ESCAPE) ? kbesc() : c;
}


/*void action()
{
    int c;

    while (1) {
        c = kbget();
        if (c == KEY_ESCAPE) {
            break;
        } else
        if (c == KEY_DOWN) {
            cursorbackward(1);
        } else
        if (c == KEY_UP) {
            cursorforward(1);
        } else
        if (c == KEY_ENTER){
            printf("\033[?1049h\033[H");
            show(list[cursorloc]);

            /*pid_t pid = fork();
            if (pid == 0) {
                execl("/usr/bin/xdg-open", "xdg-open", list[cursorloc], (char *)0);
                exit(1);
            }
            show(".");
        }
         else {
            putchar(c);
        }
}
*/