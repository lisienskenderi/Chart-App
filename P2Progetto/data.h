#ifndef DATA_H
#define DATA_H

#include "list.h"

class Data_1{
public:
    double Data;
};

class Data_2 : public Data_1{
public:
    const List<double>* Data2;
    Data_2(const List<double>* d): Data2(d){};
    Data_2(const Data_2* d): Data2(&(d->Data2)){};
};


#endif // DATA_H
