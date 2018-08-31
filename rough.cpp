#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
static struct termios initial_settings, new_settings;
static int peek_character = -1;
int kbhit_1();
int kbhit_2();
int kbhit_3();


int kbhit_1()
{
int ch=0;
tcgetattr(0,&initial_settings);
new_settings = initial_settings;
new_settings.c_lflag &= ~ICANON;
new_settings.c_lflag &= ~ECHO;
new_settings.c_lflag &= ~ISIG;
new_settings.c_cc[VMIN] = 1;
new_settings.c_cc[VTIME] = 0;
tcsetattr(0, TCSANOW, &new_settings);
ch = getchar();
tcsetattr(0,TCSANOW, &initial_settings);
if(ch='\033')
return kbhit_2();
}

int kbhit_2(){

int ch=0;
tcgetattr(0,&initial_settings);
new_settings = initial_settings;
new_settings.c_lflag &= ~ICANON;
new_settings.c_lflag &= ~ECHO;
new_settings.c_lflag &= ~ISIG;
new_settings.c_cc[VMIN] = 1;
new_settings.c_cc[VTIME] = 0;
tcsetattr(0, TCSANOW, &new_settings);
ch = getchar();
tcsetattr(0,TCSANOW, &initial_settings);
if(ch == '[')
return kbhit_3();	
}

int kbhit_3(){
int ch=0;
tcgetattr(0,&initial_settings);
new_settings = initial_settings;
new_settings.c_lflag &= ~ICANON;
new_settings.c_lflag &= ~ECHO;
new_settings.c_lflag &= ~ISIG;
new_settings.c_cc[VMIN] = 1;
new_settings.c_cc[VTIME] = 0;
tcsetattr(0, TCSANOW, &new_settings);
ch = getchar();
tcsetattr(0,TCSANOW, &initial_settings);
if(ch=='A')
printf("you pressed up\n");
else if(ch=='B')
printf("you pressed down\n");	
else  printf("bye\n");
return ch;
}
void close_keyboard()
{
tcsetattr(0, TCSANOW, &initial_settings);
}


int main()
{
int ch = 0;
while(ch!=-1){
ch = kbhit_1();
}
close_keyboard();
exit(0);
}