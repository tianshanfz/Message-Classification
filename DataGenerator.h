#ifndef DATAGENERATOR_H_INCLUDED
#define DATAGENERATOR_H_INCLUDED
#include"include.h"
#include"json/json.h"
typedef struct DataSet
{
    int **X;
    int *y;
    int m;
 //   int n;
    int *n; //n[i]表示第i组样本的特征数量
}DataSet;
class DataGenerator
{
  public:
       DataGenerator();
        ~DataGenerator();

        int GenerateData(const char* );
        DataSet& GetDataSet(){return m_dataset;}
        int GenerateDicAndAddrList(const char* dir,bool compress);
    protected:
        DataSet m_dataset;
        int GetNumberofData(const char* dir);

     //   int UpdateFeatureByWord(string newword,int* p);
        int GenerateXY(const  Json::Value& root,int i);


};


#endif // DATAGENERATOR_H_INCLUDED
