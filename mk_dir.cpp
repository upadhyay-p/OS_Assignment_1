//Priya Upadhyay
//2018202012
#include <sys/stat.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
using namespace std;

void create_dir(string dest, string dir, string home, string currdir){
	string newdir;
	//cout<<dest<<" "<<dir;
/*	cout<<(dest.substr(0,2));*/
	if((dest.substr(0,1)).compare("~")==0 || (dest.substr(0,1)).compare("/")==0){
		newdir = dest.substr(1,dest.length()-1);
		/*newdir = "/home/priya"+newdir;
		newdir = newdir + "/";
		newdir = newdir + dir;	*/
		newdir = home+"/"+newdir+"/"+dir;
		char * dirname = new char[newdir.length()+1];
		strcpy(dirname, newdir.c_str());
		//cout<<dirname;
		const int dir_err = mkdir(dirname, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		if (-1 == dir_err)
			{
    			printf("Error creating directory!1");
			}
			else printf("success");
		}

	if((dest.substr(0,1)).compare(".")==0){
		newdir = dest.substr(1,dest.length()-1);
		/*newdir = "/home/priya"+newdir;
		newdir = newdir + "/";
		newdir = newdir + dir;	*/
		newdir = currdir+"/"+newdir+"/"+dir;
		char * dirname = new char[newdir.length()+1];
		strcpy(dirname, newdir.c_str());
		//cout<<dirname;
		const int dir_err = mkdir(dirname, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		if (-1 == dir_err)
			{
    			printf("Error creating directory!1");
			}
			else printf("success");
		}

	else{
		string ans = dest + "/";
		string ans1 = ans + dir;
		char * dirname = new char[ans1.length()+1];
		strcpy(dirname, ans1.c_str());
		//cout<<dirname<<"\n";
		const int dir_err = mkdir(dirname, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		if (-1 == dir_err)
		{
    		printf("Error creating directory!2");
		}
		else printf("success");
	}
}
