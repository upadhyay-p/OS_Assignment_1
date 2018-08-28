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
#include "lib.h"
using namespace std;

#define KEY_ESCAPE  0x001b
#define KEY_ENTER   0x000a
#define KEY_UP      0x0105
#define KEY_DOWN    0x0106
#define KEY_LEFT    0x0107
#define KEY_RIGHT   0x0108

/*static struct termios term, oterm;

static int getch(void);
static int kbhit(void);
static int kbesc(void);
static int kbget(void);
static int getch(void);*/
static int cursorloc=0;
int i=0;
/*void cursorforward(int x){ 
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
void gotoxy(int x, int y)
{
printf("\x1b[%d;%dH",(x),(y));
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
    return (c == KEY_ESCAPE) ? kbesc() : c;
}*/

vector<char *> list;
void show(char argv[])
{
DIR *mydir;
struct dirent *myfile;
struct stat mystat;

mydir = opendir(argv);
while((myfile = readdir(mydir)) != NULL)
{
    //string str1 = "./";
    list.push_back(myfile->d_name);
    i++;
stat(myfile->d_name,&mystat);
printf( (S_ISDIR(mystat.st_mode)) ? "d" : "-");
printf( (mystat.st_mode & S_IRUSR) ? "r" : "-");
printf( (mystat.st_mode & S_IWUSR) ? "w" : "-");
printf( (mystat.st_mode & S_IXUSR) ? "x" : "-");
printf( (mystat.st_mode & S_IRGRP) ? "r" : "-");
printf( (mystat.st_mode & S_IWGRP) ? "w" : "-");
printf( (mystat.st_mode & S_IXGRP) ? "x" : "-");
printf( (mystat.st_mode & S_IROTH) ? "r" : "-");
printf( (mystat.st_mode & S_IWOTH) ? "w" : "-");
printf( (mystat.st_mode & S_IXOTH) ? "x" : "-");
printf("  %.*li  ",10, mystat.st_nlink);
struct passwd *pwd = getpwuid(mystat.st_uid);
printf("  %.*s  ",10,pwd->pw_name);
struct group *grp = getgrgid(mystat.st_gid);
printf("  %.*s  ",10, grp->gr_name);
printf("  %.*li  ",10,mystat.st_size);
//time
struct tm* time = gmtime(&(mystat.st_mtime));
char *t = ctime(&mystat.st_mtime);
if(t[strlen(t)-1]=='\n') t[strlen(t)-1]='\0';
printf("  %s  %s\n", t, myfile->d_name);


}
closedir(mydir);
}

void gotoxy(int x, int y)
{
printf("\x1b[%d;%dH",(x),(y));
}

int main()
{

printf("\033[?1049h\033[H");
show(".");
//This code will be used when moving to status bar fof command mode
struct winsize w;
//gotoxy(w.ws_row, w.ws_col);*/
//int x=0,y=0;
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
            printf("\033[?1049h\033[H");
            show(list[cursorloc]);
            //gotoxy(0,0);
            int num;
            scanf("%d",&num);
            /*struct winsize w;
            gotoxy(w.ws_row, w.ws_col);
            printf("%d", cursorloc);*/
        }
         else {
            putchar(c);
        }
    }
    printf("\n");

printf("\033[?1049l");
return 0;
}
