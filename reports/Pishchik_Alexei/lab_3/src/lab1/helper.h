#ifndef HELPER_H
#define HELPER_H

#include "helper_global.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class HELPER_EXPORT Helper
{

public:
    Helper();
    void destroy_file(QString s);
    string read_file_info();
    string set_apply_do(int num);

};

#endif // HELPER_H
