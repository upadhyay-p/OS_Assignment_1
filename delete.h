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

using namespace std;

void delete_file(string file, string home, string currdir){
  string newfile;
  if((file.substr(0,1)).compare("~")==0 || (file.substr(0,1)).compare("/")==0){
    newfile = file.substr(1,file.length()-1);
    newfile = home+"/"+file;
    char * fname = new char[newfile.length()+1];
    strcpy(fname, newfile.c_str());
    //cout<<dirname;
    int r_err = remove(fname);
    if (-1 == r_err)
      {
          printf("Error removing file");
      }
      else printf("success");
    }

if((file.substr(0,1)).compare(".")==0){
    newfile = file.substr(1,file.length()-1);
    newfile = currdir+"/"+file;
    char * fname = new char[newfile.length()+1];
    strcpy(fname, newfile.c_str());
    //cout<<dirname;
    int r_err = remove(fname);
    if (-1 == r_err)
      {
          printf("Error removing file");
      }
      else printf("success");
    }
  
  else{
    char * fname = new char[file.length()+1];
    strcpy(fname, file.c_str());
    //cout<<dirname<<"\n";
    int r_err = remove(fname);
    if (-1 == r_err)
    {
        printf("Error creating directory!2");
    }
    else printf("success");
  }

}

int isDirec(char* name){
  
  DIR* directory = opendir(name);
  if(directory != NULL)
  {
    closedir(directory);
    return 1;
  }
  else return 0;

}


void delete_dir(string dir, string home, string currdir){
  //cout<<dir;
  string newdir;
  if((dir.substr(0,1)).compare("~")==0 /*|| (dir.substr(0,1)).compare("/")==0*/){
    newdir = dir.substr(1,dir.length()-1);
    cout<<newdir<<"\n";
    newdir = home+newdir;
    char * dname = new char[newdir.length()+1];
    strcpy(dname, newdir.c_str());
   // cout<<dname;
    if(isDirec(dname)){
      DIR * d = opendir(dname);
      struct dirent* item;
      while((item = readdir(d)) != NULL){
         if(!strcmp(item->d_name, ".") || !strcmp(item->d_name, ".."))
          {
             continue;
          }
          else{
            string iname(item->d_name);
            string del = newdir+"/"+iname;
            /*cout<<del<<"\n";*/
            char * delc = new char[del.length()+1];
            strcpy(delc, del.c_str());
            if(!isDirec(delc)) remove(delc);
            else {string s(delc);/* cout<<"  "<<s<<"  ";*/  delete_dir(s,home,currdir);}
          }
      }
      rmdir(dname);
      printf("\ndeleted %s\n",dname);
    }

}
else{
  newdir =dir;

  char * dname = new char[newdir.length()+1];
    strcpy(dname, newdir.c_str());
   // cout<<dname;
    if(isDirec(dname)){
      DIR * d = opendir(dname);
      struct dirent* item;
      while((item = readdir(d)) != NULL){
         if(!strcmp(item->d_name, ".") || !strcmp(item->d_name, ".."))
          {
             continue;
          }
          else{
            string iname(item->d_name);
            string del = newdir+"/"+iname;
            /*cout<<del<<"\n";*/
            char * delc = new char[del.length()+1];
            strcpy(delc, del.c_str());
            if(!isDirec(delc)) remove(delc);
            else {string s(delc);/* cout<<"  "<<s<<"  ";*/  delete_dir(s,home,currdir);}
          }
      }
      rmdir(dname);
      printf("\ndeleted %s\n",dname);

}
}
}


