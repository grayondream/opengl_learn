#include "utils.h"

string GUtils::read_file(const string &filename){
    std::ifstream fp(filename, std::ios::in);

    string line = "";
    string ret_str = "";
    while(!fp.eof()){
        std::getline(fp, line);
        ret_str += line + "\n";
    }

    return ret_str;
}