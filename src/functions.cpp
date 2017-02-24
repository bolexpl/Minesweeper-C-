#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#ifdef _WIN32
#include <cstdlib>
#include <cstdio>
#endif

#include "../header/functions.h"

using namespace std;

vector<string> explode(string const & s, char delim) {
    vector<string> result;
    istringstream iss(s);

    for (string token; getline(iss, token, delim); )
    {
        result.push_back(move(token));
    }

    return result;
}

vector<int> getField(string s) {
    vector<int> result;

    bool space =false;
    for(int i=0;i<s.length();i++){
        if(s[i] == ' '){
            space = true;
        }
    }

    if(space){
        string tmp = explode(s, ' ')[0];
        vector<string> input = explode(tmp, ',');
        result.push_back(atoi(input[0].c_str()));
        result.push_back(atoi(input[1].c_str()));
    }else{
        vector<string> input = explode(s, ',');
        result.push_back(atoi(input[0].c_str()));
        result.push_back(atoi(input[1].c_str()));
    }
    return result;
}

#ifdef _WIN32
string to_string( int t )
{
    stringstream ss;
    ss << t;
    return ss.str();
}
#endif