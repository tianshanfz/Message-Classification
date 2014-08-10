#include"DataLearner.h"
#include"AddressMan.h"
#include"DictionaryMan.h"
#include"Singleton.h"
#include"include.h"
DataLearner::DataLearner()
{
    theta_word_y1=NULL;
    theta_word_y0=NULL;
    theta_addr_y1=NULL;
    theta_addr_y0=NULL;
    theta_y=0;

}
DataLearner::~DataLearner()
{
    if(theta_word_y1)
    {
        delete []theta_word_y1;
    }
    if(theta_word_y0)
    {
        delete []theta_word_y0;
    }
    if(theta_addr_y1)
    {
        delete []theta_addr_y1;
    }
    if(theta_addr_y0)
    {
        delete []theta_addr_y0;
    }
}

int DataLearner::CalWordParameters()
{
    DictionaryMan *pDicMan=Singleton<DictionaryMan>::Instance();
    int dicsize=pDicMan->GetFeatureNum();
    theta_word_y1=new double[dicsize];//Q(j|y=1)
    theta_word_y0=new double[dicsize];//Q(j|y=0)
  //   int *numxjky1=new int[dicsize];//满足Xj=k的垃圾样本数量
  ////  memset(numxjky1,0,(dicsize)*sizeof(int));
//    int *numxjky0=new int[dicsize];//满足Xj=k的非垃圾样本数量
  //  memset(numxjky0,0,(dicsize)*sizeof(int));

    vector<FeatureType> dicList=pDicMan->GetList();
    int num_y0=pDicMan->CalNormalCount();//此处统计每一各样本的每一个特征
    int num_y1=pDicMan->CalSpamCount();


    for(int k=0;k<dicsize;k++)
    {
        theta_word_y1[k]=(dicList[k].num_spam+1.0)/(num_y1+dicsize);//拉普拉斯平滑
        theta_word_y0[k]=(dicList[k].num_normal+1.0)/(num_y0+dicsize);
    }
    return 0;
}
int DataLearner::CalAddrParameters()
{
     AddressMan *pAddrMan=Singleton<AddressMan>::Instance();
    int addrsize=pAddrMan->GetFeatureNum();

     theta_addr_y1=new double[addrsize];//Q(j|y=1)
    theta_addr_y0=new double[addrsize];//Q(j|y=0)

  //     int *numxjky1=new int[addrsize];//满足Xj=k的垃圾样本数量
 //   memset(numxjky1,0,(addrsize)*sizeof(int));
 //   int *numxjky0=new int[addrsize];//满足Xj=k的非垃圾样本数量
 //   memset(numxjky0,0,(addrsize)*sizeof(int));
    vector<FeatureType> addrList=pAddrMan->GetList();
    int num_y0=pAddrMan->CalNormalCount();//此处统计每一各样本的每一个特征
    int num_y1=pAddrMan->CalSpamCount();


    for(int k=0;k<addrsize;k++)
    {
        theta_addr_y1[k]=(addrList[k].num_spam+1.0)/(num_y1+addrsize);//拉普拉斯平滑
        theta_addr_y0[k]=(addrList[k].num_normal+1.0)/(num_y0+addrsize);
    }
    int m=pAddrMan->CalDataCount();
    theta_y=num_y1*1.0/m;//计算thetay
    return 0;
}
int DataLearner::PrintParameters()
{
    int dicsize=Singleton<DictionaryMan>::Instance()->GetFeatureNum();
    int addrsize=Singleton<AddressMan>::Instance()->GetFeatureNum();

    cout<<"theta_word_y1:"<<endl;
    for(int k=0;k<dicsize;k++)
    {
        cout<<theta_word_y1[k]<<" ";
    }
    cout<<endl;
    cout<<"theta_word_y0:"<<endl;
    for(int k=0;k<dicsize;k++)
    {
        cout<<theta_word_y0[k]<<" ";
    }
    cout<<endl;
    cout<<"theta_addr_y1:"<<endl;
    for(int k=0;k<addrsize;k++)
    {
        cout<<theta_addr_y1[k]<<" ";
    }
    cout<<endl;
    cout<<"theta_addr_y0:"<<endl;
    for(int k=0;k<addrsize;k++)
    {
        cout<<theta_addr_y0[k]<<" ";
    }
    cout<<endl;
    cout<<"theta_y: "<<theta_y<<endl;
    return 0;
}
int DataLearner::ExecuteLearn()
{
    cout<<"Calculate word parameters..."<<endl;
    CalWordParameters();
    cout<<"Calculate Address parameters..."<<endl;
    CalAddrParameters();


    return 0;
}

