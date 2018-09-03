#include <stdio.h>
#include <iostream>
using namespace std; 



int rename_file(string nname, string oname, string home, string currdir)
{
  int result;
  char* oldname = new char[oname.length()+1];
  strcpy(oldname,oname.c_str());
  char* newname = new char[nname.length()+1];
  strcpy(newname, nname.c_str());
  
  result= rename( oldname , newname );
  if ( result == 0 )
    cout<<"File/folder successfully renamed";
  else
    perror( "Error renaming file" );
  return 0;
}