#include <stdio.h>
#include <iostream>
#include <cstring>
#include "runcommands.h"
//#include "cursor.h"


void commands(){
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
     		tokenize(input);

     	} else {
     		input[index] = c;
     		index++;
     	}
     	//will implement later

     	/*if(c=='\n'){
     		printf("\033")
     	}*/
     	printf("%c",c);
    }

}