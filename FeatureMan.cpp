#include"FeatureMan.h"

#include"FeatureMan.h"


int FeatureMan::GetIndex(const  string& data,int* index)
{//查找失败返回-1，index保存查找到的位置
    vector<FeatureType>::iterator it;
    int left=0;
    int right=m_FeatureList.size()-1;
     int k=(left+right)/2;
      it=m_FeatureList.begin()+k;
    while(it->data.compare(data)!=0&&left<right)
    {
        if(it->data.compare(data)>0)
        {
            right=k-1;
        }
        else if(it->data.compare(data)<0)
        {
            left=k+1;
        }
        k=(left+right)/2;
        it=m_FeatureList.begin()+k;
    }
     if(it->data.compare(data)==0)
        {//在黑名单中找到串
            *index=k;
            return 0;
        }
    //查找失败
    *index=left;
    return -1;
}
int FeatureMan::UpdateFeatureList(const  string& data,bool isspam)
{//返回在表中的索引

    FeatureType newfeature;
    newfeature.data=data;
    newfeature.num_spam=0;
    newfeature.num_normal=0;
    if(isspam==true)
    {
        newfeature.num_spam++;
    }
    else
    {
         newfeature.num_normal++;
    }

    int index=0;
    if(m_FeatureList.size()==0)
    {
        m_FeatureList.push_back(newfeature);//空表直接插入
        return 0;
    }
    else if(GetIndex(data,&index)==-1)
    {//没找到
         vector<FeatureType>::iterator it=m_FeatureList.begin()+index ;
        if(it->data.compare(data)>0)
        {
           m_FeatureList.insert(m_FeatureList.begin()+index,newfeature);//
           return index;
        }
        else
        {
            m_FeatureList.insert(m_FeatureList.begin()+index+1,newfeature);
            return index+1;
        }
    }
    //找到
    if(isspam==true)
    {
        m_FeatureList[index].num_spam++;
    }
    else
    {
         m_FeatureList[index].num_normal++;
    }

    return index;
}
int FeatureMan::Print()
{
    cout<<"**************************************"<<endl;
    cout<<"This is FeatureList:"<<endl;
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
int FeatureMan::CalDataCount()//add up numbers of appearance each feature
{
    int sum=0;
    for(unsigned int i=0;i<m_FeatureList.size();i++)
    {
        sum+=m_FeatureList[i].num_spam;
        sum+=m_FeatureList[i].num_normal;
    }
    return sum;
}
int FeatureMan::CalSpamCount()
{
    int sum=0;
    for(unsigned int i=0;i<m_FeatureList.size();i++)
    {
        sum+=m_FeatureList[i].num_spam;
    }
    return sum;
}
int FeatureMan::CalNormalCount()
{
      int sum=0;
    for(unsigned int i=0;i<m_FeatureList.size();i++)
    {
        sum+=m_FeatureList[i].num_normal;
    }
    return sum;
}
int FeatureMan::CalIG()
{//calculate IG for each feature
    int spamcount=CalSpamCount();
    int allcount=CalDataCount();
   // int normalcount=allcount-spamcount;
    double pc1=(spamcount+1.0)/(allcount+2);
    double hc=-pc1*log(pc1)/log(2.0)-(1-pc1)*log(1-pc1)/log(2.0);
    for(unsigned int i=0;i<m_FeatureList.size();i++)
    {
        double pc1t1=(m_FeatureList[i].num_spam+1.0)/(m_FeatureList[i].num_spam+m_FeatureList[i].num_normal+2.0);
        double hct1=-pc1t1*log(pc1t1)/log(2.0)-(1-pc1t1)*log(1-pc1t1)/log(2.0);
        double pc1t0=(spamcount-m_FeatureList[i].num_spam+1.0)/(allcount-m_FeatureList[i].num_spam-m_FeatureList[i].num_normal+2.0);
        double hct0=-pc1t0*log(pc1t0)/log(2.0)-(1-pc1t0)*log(1-pc1t0)/log(2.0);
        double pt1=(m_FeatureList[i].num_spam+m_FeatureList[i].num_normal)*1.0/allcount;
        double hct=pt1*hct1+(1-pt1)*hct0;
        m_FeatureList[i].IG=hc-hct;
    }

    return 0;
}
bool SortByIG( const FeatureType &v1, const FeatureType &v2)//注意：本函数的参数的类型一定要与vector中元素的类型一致
{
    return v1.IG < v2.IG;//sheng序排列 ascending sort
}
int FeatureMan::sortbyig()
{
  //  int key=0;
    for(int i=0;i<m_FeatureList.size()/2;i++)
    {
        FeatureType temp;
        temp.data=m_FeatureList[i].data;
        temp.IG=m_FeatureList[i].IG;
        temp.num_normal=m_FeatureList[i].num_normal;
        temp.num_spam=m_FeatureList[i].num_spam;
        m_FeatureList[i].data=m_FeatureList[m_FeatureList.size()-i-1].data;
        m_FeatureList[i].IG=m_FeatureList[m_FeatureList.size()-i-1].IG;
         m_FeatureList[i].num_normal=m_FeatureList[m_FeatureList.size()-i-1].num_normal;
          m_FeatureList[i].num_spam=m_FeatureList[m_FeatureList.size()-i-1].num_spam;
       m_FeatureList[m_FeatureList.size()-i-1].data=temp.data;
        m_FeatureList[m_FeatureList.size()-i-1].IG=temp.IG;
         m_FeatureList[m_FeatureList.size()-i-1].num_normal=temp.num_normal;
          m_FeatureList[m_FeatureList.size()-i-1].num_spam=temp.num_spam;
    }
    return 0;
}
int FeatureMan::CompressList()
{//Do not Compress after generating data!!!
    /*   vector<FeatureType> newlist;
     for(int i=0;i<m_FeatureList.size();i++)
     {
         if(m_FeatureList[i].num_normal<=1&&m_FeatureList[i].num_spam<=1)
        {
        }
        else
        {
            newlist.push_back(m_FeatureList[i]);
        }
     }
     m_FeatureList.clear();
     m_FeatureList=newlist;*/
 //   CalIG();
    int featureNum=m_FeatureList.size();
    int targetnum=featureNum/10;
    printf("before sort: %d ",m_FeatureList.size());
   // std::sort(m_FeatureList.begin(),m_FeatureList.end(),SortByIG);
   sortbyig();
    printf("after sort: %d ",m_FeatureList.size());
 //   m_FeatureList.erase(m_FeatureList.begin(),m_FeatureList.begin()+featureNum-targetnum);

   // freopen("ig_list.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
  //   Print();
   //  fclose(stdout);//关闭文件
    return 0;
}
