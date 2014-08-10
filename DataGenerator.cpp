#include"DataGenerator.h"

#include"DictionaryMan.h"
#include"DataParser.h"
#include"AddressMan.h"
#include"Singleton.h"

DataGenerator::DataGenerator()
{
    m_dataset.X=NULL;
    m_dataset.y=NULL;
    m_dataset.n=NULL;
}
DataGenerator::~DataGenerator()
{
    if(m_dataset.X)
    {
        for(int i = 0; i < m_dataset.m; i++)
        {
            if(m_dataset.X[i])
            {
                 delete []m_dataset.X[i];
            }
        }
        delete []m_dataset.X;
    }
    if(m_dataset.y)
    {
        delete []m_dataset.y;
    }
    if(m_dataset.n)
    {
        delete []m_dataset.n;
    }

}
 /*int DataGenerator::UpdateFeatureByWord(string newword,int* p)
 {//找到该单词在词典中的索引，并置特征向量对应位置为1
    vector<FeatureType> Dictionary=Singleton<DictionaryMan>::Instance()->GetList();
    for(unsigned int i=0;i<Dictionary.size();i++)
    {
        if(Dictionary[i].data->compare(newword)==0)
        {//已经出现过的单词
            p[i]=1;
            return 0;
        }
        else if(Dictionary[i].compare(newword)>0)
        {//找到第一个比新单词大的位置,表示词典中无此单词
           return -1;
        }
    }
    //无此单词
    return -1;
 }*/


 int DataGenerator::GenerateXY(const  Json::Value& root,int i)
 {
    string body = root["body"].asString();
    vector<string> words;
    Singleton<DataParser>::Instance()->ParseMsg(body,words);
    vector<int> featurelist;
      for(unsigned int j=0;j<words.size();j++)
     {//将分解的词在字典中找到索引
         int index;
        int found=Singleton<DictionaryMan>::Instance()->GetIndex(words[j],&index);
        if(found!=-1)
        {
            featurelist.push_back(index);
        }
     }
    m_dataset.n[i]=featurelist.size()+1;//第i个数据的特征数
    m_dataset.X[i]=new int[m_dataset.n[i]];//生成第i个数据的特征
    for(unsigned int j=0;j<featurelist.size();j++)
    {
        m_dataset.X[i][j]=featurelist[j];
    }
    string addr=root["address"].asString();

    int found=Singleton<AddressMan>::Instance()->GetIndex(addr,&m_dataset.X[i][ m_dataset.n[i]-1]);//最后一个特征表示地址索引
    if(found==-1)
    {//not found addr
        m_dataset.X[i][ m_dataset.n[i]-1]=-1;
    }
    string isspam=root["spam"].asString();
    if(isspam.compare("true")==0)
    {
        m_dataset.y[i]=true;
    }
    else
    {
        m_dataset.y[i]=false;
    }

    return 0;
 }
 int DataGenerator::GenerateDicAndAddrList(const char* dir,bool bcompress)
 {//return numer of datas
    ifstream filedata(dir);
    if(!filedata)
    {
        std::cout<<"fail opening file !"<<endl;
        return -1;
    }
    Json::Reader reader;
    Json::Value root;
    char buf[MAX_LENGTH_OF_ALINE];
    filedata.getline(buf,MAX_LENGTH_OF_ALINE);
    int num_data=0;
    for( num_data=0;!filedata.eof();num_data++)
    {
        if(num_data%1000==0)
        {
            cout<<"Generating dictionary..."<<num_data<<endl;
        }
           if(!reader.parse(buf,root,false))
        {
            cout<<"fail reading file!"<<endl;
            return -1;
        }
        string strisspam=root["spam"].asString();
        bool isspam=false;
        if(strisspam.compare("true")==0)
        {
            isspam=true;
        }
        string body = root["body"].asString();
        vector<string> words;
         Singleton<DataParser>::Instance()->ParseMsg(body,words);
         for(unsigned int i=0;i<words.size();i++)
         {//将分解的词更新至词典
                Singleton<DictionaryMan>::Instance()->UpdateFeatureList(words[i],isspam);
         }
        string addr=root["address"].asString();
         Singleton<AddressMan>::Instance()->UpdateFeatureList(addr,isspam);
         filedata.getline(buf,MAX_LENGTH_OF_ALINE);
    }
    filedata.close();
    if(bcompress)
    {
         Singleton<DictionaryMan>::Instance()->CompressList();
    }

  //  Singleton<AddressMan>::Instance()->CompressList();
  //  Singleton<DictionaryMan>::Instance()->Print();
   // Singleton<AddressMan>::Instance()->Print();
    return num_data;
 }
 int DataGenerator::GetNumberofData(const char* dir)
 {//return numer of datas
    ifstream filedata(dir);
    if(!filedata)
    {
        std::cout<<"fail opening file !"<<endl;
        return -1;
    }
    Json::Reader reader;
    Json::Value root;
    char buf[MAX_LENGTH_OF_ALINE];
    filedata.getline(buf,MAX_LENGTH_OF_ALINE);
    int num_data=0;
    for( num_data=0;!filedata.eof();num_data++)
    {
        if(!reader.parse(buf,root,false))
        {
            cout<<"fail reading file!"<<endl;
            return -1;
        }
        filedata.getline(buf,MAX_LENGTH_OF_ALINE);
    }
    filedata.close();
    return num_data;
 }
int DataGenerator::GenerateData(const char* dir)
{
    int num_of_data=GetNumberofData(dir);
    if(num_of_data<0)
    {
        return -1;
    }
    m_dataset.m=num_of_data;
    m_dataset.y=new int[m_dataset.m];//输出值
     m_dataset.X=new int*[m_dataset.m];//输入样本
     memset(m_dataset.X,0,m_dataset.m*sizeof(int*));
     m_dataset.n=new int[m_dataset.m];
    ifstream filedata(dir);
    Json::Reader reader;
    Json::Value root;
    char buf[MAX_LENGTH_OF_ALINE];
    filedata.getline(buf,MAX_LENGTH_OF_ALINE);
    for(int i=0;!filedata.eof();i++)
    {
        if(i%1000==0)
        {
                cout<<"Generating data:"<<i<<endl;
        }
        reader.parse(buf,root,false);
        GenerateXY(root,i);
        filedata.getline(buf,MAX_LENGTH_OF_ALINE);

    }
    filedata.close();
    return 0;
}
