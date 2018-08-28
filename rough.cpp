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

vector<string> files;
int i=0;

void show(char argv[])
{
DIR *mydir;
struct dirent *myfile;
struct stat mystat;

mydir = opendir(argv);
while((myfile = readdir(mydir)) != NULL)
{
	files.push_back(myfile->d_name);
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

int main()
{

printf("\033[?1049h\033[H");
show(".");
//This code will be used when moving to status bar fof command mode
/*struct winsize w;
gotoxy(w.ws_row, w.ws_col);*/
//int x=0,y=0;
//gotoxy(0,0);
cout<<"\n\n";

for(auto j = files.begin(); j!=files.end();j++){
	cout<<(*j);
}
    int c;

    scanf("%d",&c);

printf("\033[?1049l");
return 0;
}
