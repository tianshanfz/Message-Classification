#include"include.h"
#include"DictionaryMan.h"
#include"DataGenerator.h"
#include"DataLearner.h"
#include"Singleton.h"
#include"DataPredictor.h"
#include"jieba/MixSegment.hpp"


int GenerateDataFile()
{
    ifstream ifile("data/merged_2.json");

     ofstream crossfile("data/cross.json");
    ofstream testfile("data/test.json");
    ofstream trainfile("data/train.json");

    char buf[MAX_LENGTH_OF_ALINE];
    ifile.getline(buf,MAX_LENGTH_OF_ALINE);
    int num_data=0;
    srand((unsigned)time(0));
    for( num_data=0;!ifile.eof();num_data++)
    {
        strcat(buf,"\n");
        int randomnum=rand()%6;
        if(randomnum==0)
        {
            testfile.write(buf,strlen(buf));
        }
        else if(randomnum==1)
        {
            crossfile.write(buf,strlen(buf));
        }
        else
        {
            trainfile.write(buf,strlen(buf));
        }

        ifile.getline(buf,MAX_LENGTH_OF_ALINE);
    }
    ifile.close();
    crossfile.close();
    trainfile.close();
    testfile.close();
    return 0;

}

int main()
{
    GenerateDataFile();
 /*   //生成词典
    Singleton<DirectoryMan>::Instance()->GenerateDirectory("/home/han/Desktop/machine_learning/url_spam/training_data.txt");
   // Singleton<DirectoryMan>::Instance()->Print();*/
   //生成训练数据
   DataGenerator traindata;
   traindata.GenerateDicAndAddrList("data/train.json",false);

 //   DataSet dataset_train= traindata.GetDataSet();
    //学习
    Singleton<DataLearner>::Instance()->ExecuteLearn();

  //  Singleton<DataLearner>::Instance()->PrintParameters();

    //得到测试数据
    DataGenerator crossdata;
    crossdata.GenerateData("data/cross.json");

    DataSet dataset_cross=crossdata.GetDataSet();
    Singleton<DataPredictor>::Instance()->PredictData(dataset_cross.X,dataset_cross.y,dataset_cross.n,dataset_cross.m,true);

    DataGenerator testdata;
    testdata.GenerateData("data/test.json");

    DataSet dataset_test=testdata.GetDataSet();
    Singleton<DataPredictor>::Instance()->PredictData(dataset_test.X,dataset_test.y,dataset_test.n,dataset_test.m);



    return 0;
}
