#ifndef __GLOG_H__
#define __GLOG_H__

#include <string>

using std::string;

enum GLOG_TYPE{
    GLOG_UNKNOWN,
    GLOG_INFO,
    GLOG_WARNING,
    GLOG_ERROR
};


#define ilog(msg) glog(GLOG_INFO, (msg), __FILE__, __LINE__);
#define wlog(msg) glog(GLOG_WARNING, (msg), __FILE__, __LINE__);
#define elog(msg) glog(GLOG_ERROR, (msg), __FILE__, __LINE__);

void glog(GLOG_TYPE type, const string &msg, const string &file, int line){
    string type_str = "unknown";
    switch (type)
    {
    case GLOG_UNKNOWN:
        type_str = "unknown";
        break;
    case GLOG_INFO:
        type_str = "info";
        break;
    case GLOG_WARNING:
        type_str = "warning";
        break;
    case GLOG_ERROR:
        type_str = "error";
        break;
    default:
        type_str = "unknown";
        break;
    }

    fprintf(stderr, "[%s] %4d %s %s\n", type_str.c_str(), line, file.c_str(), msg.c_str());
}

#endif //__GLOG_H__