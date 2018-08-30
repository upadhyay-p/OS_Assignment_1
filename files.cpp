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
#include "ls.h"
//#include "start.h"
using namespace std;
string path;

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

int main()
{
printf("\033[?1049h\033[H");

//getting current working directory in absp
char absp[1000];
string d = getcwd(absp,1000);
string slash="/";
//showing list of files/directories in cwd
show(d.append("/"));
//show("/home/priya/OS_Assignment_1/OS_Assignment_1/demoFolder");
struct winsize w;

//setting cursor to top of the list
gotoxy(0,0);

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
            //entering a new directory
            printf("\033[?1049h\033[H");
            //showing list of files for new directory
            //string cd = getcwd(absp,1000);
            //string cd = list[0];
            //cd.append(list[cursorloc+1]);
            //cout<<g<<" ";
            //cout<<cd<<" ";
            show(list[0]+list[cursorloc+1]);
            //cout<<list[cursorloc]<<"\n";  

            //gotoxy(0,0);
            //cursorloc =0;

            //will deal with this later
            /*pid_t pid = fork();
            if (pid == 0) {
                execl("/usr/bin/xdg-open", "xdg-open", list[cursorloc], (char *)0);
                exit(1);
            }
            show(".");
            */
        } else
        if (c == KEY_LEFT) {
             printf("\033[?1049h\033[H");
             show(list[0]+"..");
             gotoxy(0,0);
        }
         else {
            putchar(c);
        }
    }
    printf("\n");

printf("\033[?1049l");
return 0;
}