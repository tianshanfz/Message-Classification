#ifndef ADDRESSMAN_H_INCLUDED
#define ADDRESSMAN_H_INCLUDED
#include"include.h"
#include"FeatureMan.h"
class AddressMan :public FeatureMan
{
  public:
        AddressMan();
        virtual ~AddressMan();
        int Print();
    protected:
};

#endif // ADDRESSMAN_H_INCLUDED
