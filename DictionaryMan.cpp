#include"DictionaryMan.h"

DictionaryMan::DictionaryMan()
{

}
DictionaryMan::~DictionaryMan()
{

}
bool DictionaryMan::IsNumAlphabet(char c)
{
    if(c<='z'&&c>='a')
    {
        return true;
    }
    if(c<='9'&&c>='0')
    {
        return true;
    }
    if(c>='A'&&c<='Z')
    {
        return true;
    }
    return false;
}

int DictionaryMan::Print()
{
    cout<<"**************************************"<<endl;
    cout<<"This is Dictionary:"<<endl;
    for(unsigned int i=0;i<m_FeatureList.size();i++)
    {
       cout<<m_FeatureList[i].data<<"  ";
        cout<<m_FeatureList[i].num_spam<<"  ";
         cout<<m_FeatureList[i].num_normal<<"   ";
        cout<<m_FeatureList[i].IG<<endl;
    }

    cout<<"**************************************"<<endl;
    return 0;
}
