#ifndef FEATUREMAN_H_INCLUDED
#define FEATUREMAN_H_INCLUDED
#include"include.h"
typedef struct FeatureType
{
    string data;//feature word
    int num_spam;//number of appearance times in spam message
    int num_normal;//... appearance times in normal message
    double IG;
}FeatureType;

class FeatureMan
{
    public:
        FeatureMan(){};
        virtual ~FeatureMan(){};

        int GetIndex(const  string& ,int* index);
        virtual int UpdateFeatureList(const  string& ,bool isspam);
        virtual vector<FeatureType>& GetList(){return m_FeatureList;}
        int GetFeatureNum(){return m_FeatureList.size();}
        int CalDataCount();//add up numbers of appearance each feature
        int CalSpamCount();
        int CalNormalCount();
        int CompressList();
        virtual int Print();
  protected:
        int CalIG();
        int sortbyig();
        vector<FeatureType> m_FeatureList;


};
#endif // FEATUREMAN_H_INCLUDED
