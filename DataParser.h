#ifndef DATAPARSER_H_INCLUDED
#define DATAPARSER_H_INCLUDED
#include"include.h"
#include"jieba/MixSegment.hpp"
class DataParser
{
    public:
        DataParser();
        virtual ~DataParser();
        int ParseMsg(const string& msg, vector<string>&  words);
        int ParseUrl(string url);
    protected:
        CppJieba::MixSegment mixseg;

};

#endif // DATAPARSER_H_INCLUDED
