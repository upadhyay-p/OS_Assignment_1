#ifndef LS_H
#define LS_H
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
#include<stack>
#include "cursor.h"
using namespace std;

//extern int i; iski jagah flecount likha h
extern int filecount;
extern string path;
extern int clear_fwd;
extern int push;
int rowcount;
int start;
int end;
void show (string);
extern vector<string> list;
extern stack<string> fwdkey;
extern stack<string> backkey;

void openFile(char* path_name){
	pid_t pid = fork();
	if (pid == 0) {
		execl("/usr/bin/xdg-open", "xdg-open",path_name, (char *)0);
	}
	show(list[0]);
}

int isDir(char * name){
	DIR* directory = opendir(name);
	if(directory != NULL)
	{
		string s(name);
		backkey.push(s);
		closedir(directory);
		return 1;
	}
	else return 0;

}

void store(string path_name){
	filecount=0;
	cursorloc=0;
	DIR *mydir;
	struct dirent *myfile;
	char * cpath = new char [path_name.length()+1];
	strcpy (cpath, path_name.c_str());
	mydir = opendir(cpath);
	list.push_back(path_name);

    //clearing fwd stack when enter is pressed 
	if(clear_fwd==1){
		while(!fwdkey.empty()) fwdkey.pop();
	}


	while((myfile = readdir(mydir)) != NULL)
	{
		string s(myfile->d_name);

	//list.push_back("/"+s);
		list.push_back(s);
		filecount++;
	}
}

void show(string path_name)
{
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	/*rowcount = w.ws_row;
	rowcount = rowcount-2;*/
	char * cpath = new char [path_name.length()+1];
	strcpy (cpath, path_name.c_str());
	if(isDir(cpath))
	{
		list.clear();
		store(path_name);
		DIR *mydir;
		//struct dirent *myfile;
		struct stat mystat;
		mydir = opendir(cpath);
		char fullpath[1000];
		start=1;
		while(start<= filecount) //(myfile = readdir(mydir)) != NULL &&
		{
			char* l = new char[list[0].length()+1];
			strcpy(l, list[0].c_str());
			char* name = new char[list[start].length()+1];
			strcpy(name, list[start].c_str());
			snprintf(fullpath, sizeof(fullpath), "%s/%s", l, name);
			stat(fullpath,&mystat);
//itr++;
//printf(" %s", myfile->d_name );
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
			printf("   %li  ", mystat.st_nlink);
			struct passwd *pwd = getpwuid(mystat.st_uid);
			printf("   %s  ",pwd->pw_name);
			struct group *grp = getgrgid(mystat.st_gid);
			printf("    %s  ", grp->gr_name);
			printf("%10li  ",mystat.st_size);
//time
			char *t = ctime(&mystat.st_mtime);
			if(t[strlen(t)-1]=='\n') t[strlen(t)-1]='\0';
			printf("  %s    %s \n", t, name);
			start++;
		}
		closedir(mydir);
		printf("\033[0;0H");
	}

	else {
		openFile(cpath);
	}
}

#endif