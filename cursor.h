//Priya Upadhyay
//2018202012
#ifndef CURSOR_H
#define CURSOR_H
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
#define H_KEY       0x0048
#define h_KEY       0x0068
#define BACKSPACE   0x7f

static struct termios term, oterm;

static int getch(void);
static int kbhit(void);
static int kbesc(void);
static int kbget(void);
static int getch(void);
int cursorloc=0;

//int i; iski jagah fileno likha h
int filecount;
extern vector<string> list;
extern string home;
extern int normal_mode;
extern int clear_fwd;
extern int rowcount;
extern int start;

void cursorup(int x){ 
    if(cursorloc>0){
    printf("\033[%dA", x);
    cursorloc--;
}
}

void cursordown(int x) {
    if(cursorloc<filecount-1){
    printf("\033[%dB", x);
    cursorloc++;
}
}


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
            case 'D':
                c = KEY_LEFT;
                break;
            case 'C':
                c = KEY_RIGHT;
                break;
            default:
                c = 0;
                break;
        }
    } else
    if(c == '?'){
        c = BACKSPACE;
    }
     else {
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
        return c;
    }
    else if(c==H_KEY ||c==h_KEY){
        return c;
    }
}

#endif