#ifndef __UTILS_H__
#define __UTILS_H__

#include <cstdio>
#include <string>
#include <fstream>

using std::string;
using std::fstream;

class GUtils{
public:
    static string read_file(const string &filename);  
};

#endif //__UTILS_H__