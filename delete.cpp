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


int delete_dir(const char *path)
{
   DIR *d = opendir(path);
   size_t path_len = strlen(path);
   int r = -1;

   if (d)
   {
      struct dirent *p;

      r = 0;

      while (!r && (p=readdir(d)))
      {
          int r2 = -1;
          char *buf;
          size_t len;

          /* Skip the names "." and ".." as we don't want to recurse on them. */
          if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
          {
             continue;
          }

          len = path_len + strlen(p->d_name) + 2; 
          buf =(char*) malloc(len);

          if (buf)
          {
             struct stat statbuf;

             snprintf(buf, len, "%s/%s", path, p->d_name);

             if (!stat(buf, &statbuf))
             {
                if (S_ISDIR(statbuf.st_mode))
                {
                   r2 = remove_directory(buf);
                }
                else
                {
                   r2 = unlink(buf);
                }
             }

             free(buf);
          }

          r = r2;
      }

      closedir(d);
   }

   if (!r)
   {
      r = rmdir(path);
   }

   return r;
}

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