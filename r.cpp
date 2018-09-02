#include<stdio.h>
#include<iostream>
using namespace std;

int main(){
	char arr[5];
	int i=0;
	while(i<5){
		char c = getchar();
		arr[i] = c;
		i++;
	}

	i=0;
	while(i<5){
		cout<<arr[i];
		i++;
	}
	return 0;
}