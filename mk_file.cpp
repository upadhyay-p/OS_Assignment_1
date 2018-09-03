//Priya Upadhyay
//2018202012
#include <sys/stat.h>
#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
using namespace std;

void create_file(string dest, string fname, string home, string currdir){
	string newfile;
	//cout<<dest<<" "<<dir;
/*	cout<<(dest.substr(0,2));*/
	if((dest.substr(0,1)).compare("~")==0 || (dest.substr(0,1)).compare("/")==0){
		newfile = dest.substr(1,dest.length()-1);	
		newfile = home+"/"+newfile+"/"+fname;
		char * filename = new char[newfile.length()+1];
		strcpy(filename, newfile.c_str());
		//cout<<dirname;
		const int file_err = open(filename, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		if (-1 == file_err)
		{
			printf("Error creating file");
		}
		else printf("success");
	} 
	else if((dest.substr(0,1)).compare(".")==0)
	{
		newfile = dest.substr(1,dest.length()-1);
		newfile = currdir+"/"+newfile+"/"+fname;	
		char * filename = new char[newfile.length()+1];
		strcpy(filename, newfile.c_str());
		//cout<<dirname;
		const int file_err = open(filename,O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		if (-1 == file_err)
		{
			printf("Error creating file");
		}
		else printf("success");
	} 
	else{
		string ans = dest + "/";
		string ans1 = ans + fname;
		char * filename = new char[ans1.length()+1];
		strcpy(filename, ans1.c_str());
		//cout<<dirname<<"\n";
		const int file_err = open(filename,O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH );
		if (-1 == file_err)
		{
			printf("Error creating file");
		}
		else printf("success");
	}
}
