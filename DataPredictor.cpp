#include"DataPredictor.h"
#include"DataLearner.h"
#include"Singleton.h"
#include"include.h"
DataPredictor::DataPredictor()
{
    predict_res=NULL;
    m_threashold=0.5;
}
DataPredictor::~DataPredictor()
{
    if( predict_res==NULL)
    {
        delete []predict_res;
    }
}
double PredictorSingleData(int* feature,int res,int n)
{
     double py1=1;
    double py0=1;
    if(feature[n-1]!=-1)
    {
        py1=Singleton<DataLearner>::Instance()->GetThetaAddrjky1(feature[n-1]);
        py0=Singleton<DataLearner>::Instance()->GetThetaAddrjky0(feature[n-1]);
    }

    for(int j=0;j<n-1;j++)
    {

            py1*=Singleton<DataLearner>::Instance()->GetThetaWordjky1(feature[j]);
            py0*=Singleton<DataLearner>::Instance()->GetThetaWordjky0(feature[j]);
    }
    double theta_y1=Singleton<DataLearner>::Instance()->GetThetaY1();
    double theta_y0=Singleton<DataLearner>::Instance()->GetThetaY0();
    return py1*theta_y1/(py1*theta_y1+py0*theta_y0);
}
 int DataPredictor::PredictData(int** X,int *y,int* n,int m,bool IsAdjust)
 {
     predict_res=new int[m];
     double *predict_res_double=new double[m];
    for(int i=0;i<m;i++)
    {
        predict_res_double[i]=PredictorSingleData(X[i],y[i],n[i]);
    }
    if(IsAdjust)
    {//调整threashold
        double predict=0;
        double recall=0;
        double fscore=0;
        double temp_threashold=0.1;
        for(;temp_threashold<0.9;temp_threashold+=0.05)
        {
            int count_true_pos=0;
            int count_pos=0;
             int count_true=0;
             for(int i=0;i<m;i++)
            {
                if(predict_res_double[i]>temp_threashold)
                {
                    count_pos++;
                }
                if(y[i]==1)
                {
                    count_true++;
                }
                if(predict_res_double[i]>temp_threashold&&y[i]==1)
                {
                    count_true_pos++;
                }
            }
            predict=count_true_pos*1.0/count_pos;
            recall=count_true_pos*1.0/count_true;
            double temp_fscore=predict*recall/(predict+recall);
            if(temp_fscore>fscore)
            {//得到最大的fscore对应的threashold
                fscore=temp_fscore;
                m_threashold=temp_threashold;
            }
        }
    }
    cout<<endl<<m_threashold<<endl;
    cout<<"predict:"<<endl;
    for(int i=0;i<m;i++)
    {
        if(predict_res_double[i]>m_threashold)
        {
            predict_res[i]=1;
        }
        else
        {
            predict_res[i]=0;
        }
        cout<<predict_res[i];
    }
    int rightnum=0;
    cout<<endl<<"y:"<<endl;
    for(int i=0;i<m;i++)
    {
        cout<<y[i];
        if(y[i]==predict_res[i])
        {
            rightnum++;
        }
    }
    cout<<"accuraty rate: "<<rightnum*1.0/m;
    delete []predict_res_double;
    return 0;
 }

