#include"AddressMan.h"

AddressMan::AddressMan()
{

}
AddressMan::~AddressMan()
{
}
int AddressMan::Print()
{
    cout<<"**************************************"<<endl;
    cout<<"This is AddrList:"<<endl;
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
