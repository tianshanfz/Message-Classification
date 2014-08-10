#ifndef DICTIONARYMAN_H_INCLUDED
#define DICTIONARYMAN_H_INCLUDED
#include"include.h"

#include"FeatureMan.h"
class DictionaryMan :public FeatureMan
{

  public:
        DictionaryMan();
        virtual ~DictionaryMan();
     //    int GenerateDictionary(const char* dir);
        int Print();
            bool IsNumAlphabet(char c);//判断字符是否是字母数字
   protected:

   //     vector<string> m_UrlDictionary;
    //    int OnAddNewWord(string newword);
};
#endif // DIRECOTYMAN_H_INCLUDED
