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
using namespace std;

extern int i;
extern string path;

vector<string> list;

/*struct fnode{
	string name;
	string parent;
	string fwd;
	string back;
};
*/
/*vector<struct fnode*> list;
void create_fnode(string n, string p){
	struct fnode* cnode = (struct fnode*) malloc(sizeof(struct fnode));
	cnode->name = n;
	cout<<cnode->name<<"\n";
	cnode->parent = p;
	list.push_back(cnode);
	//return cnode;
	free(cnode);
}
*/

void openFile(string path_name){
	pid_t pid = fork();
            if (pid == 0) {
                execl("/usr/bin/xdg-open", "xdg-open",path_name, (char *)0);
                exit(1);
            }
}

int isDir(char * name){
	DIR* directory = opendir(name);
    if(directory != NULL)
    {
     closedir(directory);
     return 1;
    }
    else return 0;

}

void store(string path_name){
	i=0;
	cursorloc=0;
	DIR *mydir;
    struct dirent *myfile;
    char * cpath = new char [path_name.length()+1];
    strcpy (cpath, path_name.c_str());
    mydir = opendir(cpath);
    list.push_back(path_name);
    while((myfile = readdir(mydir)) != NULL)
{
	string s(myfile->d_name);

	list.push_back("/"+s);
	i++;
}
/*for(auto it = list.begin(); it!=list.end(); it++){
	cout<<(*it)<<"\n";
}*/
}

void show(string path_name)
{
	char * cpath = new char [path_name.length()+1];
    strcpy (cpath, path_name.c_str());
    //cout<<cpath<<" ";
	if(isDir(cpath))
	{
		list.clear();
	store(path_name);
	//initializing vector iterator
	/*int i=0;
	cursorloc=0;*/
	//c_str; converting string path to char array 

	//list.clear();
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
    mydir = opendir(cpath);
while((myfile = readdir(mydir)) != NULL)
{
	//strcat(cpath,myfile->d_name);
	//string s = cpath;
    //create_fnode(cpath,s.append(myfile->d_name));
    //strcat(cpath,myfile->d_name)
    //list.push_back(myfile->d_name);
    //i++;
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
/*for(int j=0;j<i;i++){
	cout<<list[i]->name<<"  ";
}
*/
closedir(mydir);
printf("\033[0;0H");
}

else {
//openFile(path_name);
	cout<<path_name;
}
}
