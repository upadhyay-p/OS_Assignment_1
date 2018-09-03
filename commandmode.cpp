//Priya Upadhyay
//2018202012
#include <stdio.h>
#include <iostream>
#include <cstring>
#include "runcommands.h"
//#include "cursor.h"



void commands(string home, string currdir){
	 struct winsize w;
     ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
     printf("\033[%d;%dH", w.ws_row,0);
     string str;
     char c;
     int index=0;
     char input[100];
     while(1){
     	c = kbget();
     	if (c == KEY_ESCAPE) {
     		normal_mode=1;
     		break;
     	} else
     	if(c == KEY_ENTER) {
     		input[index] = '\0';
     		tokenize(input,home,currdir);

     	} /*else
     	if(c == BACKSPACE){				//implement backspace later
     		printf("\b");
     		index--;

     	}*/ else {
     		input[index] = c;
     		index++;
     	}
     	if(c!='\n')
     	printf("%c",c);
    }

}