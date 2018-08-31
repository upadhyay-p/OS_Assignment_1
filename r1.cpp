#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>

int main()
{
	int c = getchar();
	if(c==0x7f)
	printf("Hello hi this is priya");
	return 0;
}