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
#include "cursor.h"
#include "ls.h"
using namespace std;

#define KEY_ESCAPE  0x001b
#define KEY_ENTER   0x000a
#define KEY_UP      0x0105
#define KEY_DOWN    0x0106
#define KEY_LEFT    0x0107
#define KEY_RIGHT   0x0108

void gotoxy(int x, int y)
{
printf("\x1b[%d;%dH",(x),(y));
}

void open(char argv[])
{
	show(argv);
struct winsize w;
gotoxy(4,0);

    int c;
    i=0;
    cursorloc=0;
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
            open(list[cursorloc]);

            gotoxy(0,0);
            int num;
            scanf("%d",&num);

            /*pid_t pid = fork();
            if (pid == 0) {
                execl("/usr/bin/xdg-open", "xdg-open", list[cursorloc], (char *)0);
                exit(1);
            }
            show(".");
            */
        }
         else {
            putchar(c);
        }
    }
    printf("\n");

}