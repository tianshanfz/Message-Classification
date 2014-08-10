#include"DataParser.h"
#include"DictionaryMan.h"
DataParser::DataParser():mixseg("/home/han/Desktop/machine_learning/url_spam/SVM/cppjieba-master/dict/jieba.dict.utf8",
                                "/home/han/Desktop/machine_learning/url_spam/SVM/cppjieba-master/dict/hmm_model.utf8")
{

}
DataParser::~DataParser()
{

}

int DataParser::ParseMsg(const string& msg, vector<string>& words)
{
    vector<string> cutres;
     mixseg.cut(msg,cutres);
    for(unsigned int i=0;i<cutres.size();i++)
    {
        if(mixseg.inDict(cutres[i])==true)
        {//是中文词
            words.push_back(cutres[i]);
        }
        else
        {
            if(cutres[i].size()>3)
            {// 非中文 长度大于3才计入表
                words.push_back(cutres[i]);
            }
        }
    }
     return 0;
}
int DataParser::ParseUrl(string url)
{
return 0;
}
