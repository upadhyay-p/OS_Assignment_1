#include <stdio.h>
#include <iostream>
#include <cstring>
#include "mk_dir.h"
#include "mk_file.h"

 
vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}


void tokenize(char * input){

	vector <string> toks = split(input," ");
 	//string s(input);
	//string delimiter = " ";

	/*size_t pos = 0;
	string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
    	token = s.substr(0, pos);
    	std::cout << token << std::endl;
    	toks.push_back(token);
    	s.erase(0, pos + delimiter.length());
	}*/
	string dest = toks.back();
	toks.pop_back();
	string cmd = toks[0];

    if(cmd.compare("create_dir")==0){
    		create_dir(dest,toks[1]);
    }

    if(cmd.compare("create_file")==0){
    		create_file(dest,toks[1]);
    }
	//cout<<toks[0]<<"\n"<<toks[1]<<"\n"<<toks[2];
	//string s(input);
	
}