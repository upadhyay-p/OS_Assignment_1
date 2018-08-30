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

vector<struct fnode*> files;
int i=0;

struct fnode{
	string name;
	long int size;
};

struct fnode* create_node(string name, long int s){
	struct fnode* c = (struct fnode *)malloc(sizeof(struct fnode));
	c->name=name;
	c->size = s;
	return c;
}

/*struct fnode cn(string name, long int s){
	struct node c1;
	struct fnode* c = (struct fnode *)malloc(sizeof(struct fnode));
	c=c1
	c1.name =name;
	c1.size = s;
	return c1;
}
*/
int main(){

	files.push_back(create_node("twoo",19));
	files.push_back(create_node("one",20));
	files.push_back(create_node("three",43));


	for(int i=0;i<3;i++){
		cout<<files[i]->name<<","<<files[i]->size<<"\n";
	}
	return 0;
}