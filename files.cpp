//Priya Upadhyay
//2018202012
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
#include "commandmode.h"
//#include "start.h"
using namespace std;
string path;
string home;
int normal_mode=1;
int push=1;
//int backspace_off=0;
int clear_fwd = 0;
extern int cursorloc;
vector<string> list;
stack<string> fwdkey;
stack<string> backkey;

#define KEY_ESCAPE  0x001b
#define KEY_ENTER   0x000a
#define KEY_UP      0x0105
#define KEY_DOWN    0x0106
#define KEY_LEFT    0x0107
#define H_KEY       0x0048
#define h_KEY       0x0068
#define KEY_RIGHT   0x0108
#define COLON       0x003a

void gotoxy(int x, int y)
{
printf("\x1b[%d;%dH",(x),(y));
}

int main()
{
    getchar();
printf("\033[?1049h\033[H");

//getting current working directory in absp
char absp[1000];
home = getcwd(absp,1000);
//showing list of files/directories in cwd
show(home);
//show("/home/priya/OS_Assignment_1/OS_Assignment_1/demoFolder");
//struct winsize w;

//setting cursor to top of the list
gotoxy(0,0);

    int c;

    while (1) {
        c = kbget();
        if (c == KEY_ESCAPE) {
            if(normal_mode)
                break;
            else{
                normal_mode=1;
                printf("\033[?1049h\033[H");
                show(fwdkey.top());
                gotoxy(0,0);
            }

        } else
        if (c == KEY_DOWN) {
            cursordown(1);
        } else
        if (c == KEY_UP) {
            cursorup(1);
        } else
        if (c == KEY_ENTER){
            //entering a new directory
            clear_fwd = 1;
            printf("\033[?1049h\033[H");
           // if(list[0].compare(home)!=0 && list[cursorloc+1].compare("..")!=0){
            if((list[0]+"/"+list[cursorloc+1]).compare(home+"/..")!=0)
            show(list[0]+"/"+list[cursorloc+1]);
        else {show(home);}
        //}
            
        } else
        if (c == BACKSPACE && normal_mode) {
            clear_fwd=0;
             printf("\033[?1049h\033[H");
             size_t slash = list[0].find_last_of("/");
             string back = list[0].substr(0,slash);
             string homeback = home.substr(0,home.find_last_of("/"));
             //show(list[0]+"/..");
             if(back.compare(homeback)!=0)
             {show(back); gotoxy(0,0);}
             else {show(home);}
        }  else
        if (c == KEY_LEFT && normal_mode) {
             if(!backkey.empty())
             {
                 clear_fwd=0;
                 printf("\033[?1049h\033[H");
                 fwdkey.push(backkey.top());
                 backkey.pop();
                 if(!backkey.empty()){
                 string s = backkey.top();
                 fwdkey.push(s); //experiment
                 backkey.pop();
                 show(s);
                 gotoxy(0,0);}
            }
        } else
        if (c == KEY_RIGHT && normal_mode) {
             if(!fwdkey.empty())
             {
                 clear_fwd=0;
                 printf("\033[?1049h\033[H");
                 backkey.push(fwdkey.top());
                 fwdkey.pop();
                 if(!fwdkey.empty())
                 {string s = fwdkey.top();
                    backkey.push(s); //experiment
                 fwdkey.pop();
                 show(s);
                 gotoxy(0,0);}
            }
        } else 
        if(c==H_KEY ||c==h_KEY){
            kbhit();
            printf("\033[?1049h\033[H");
            show(home);
        } else 
        if(c== COLON){
            normal_mode=0;
            commands(home,list[0]);
            gotoxy(0,0);
        } else {
            continue;
        }
    }
    printf("\n");

//printf("\033[?1049l");
return 0;
}