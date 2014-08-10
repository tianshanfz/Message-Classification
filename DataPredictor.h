#ifndef DATAPREDICTOR_H_INCLUDED
#define DATAPREDICTOR_H_INCLUDED

class DataPredictor
{
 public:
       DataPredictor();
        ~DataPredictor();
        int PredictData(int** X,int *y,int* n,int m,bool IsAdjust=false);//最后一个参数标明是否根据结果调整threashold

    protected:
        double AdjustThreashold(int* y, int* predict,int m);
        int *predict_res;
        double  m_threashold;//概率大于多少时判定为垃圾

};


#endif // DATAPREDICTOR_H_INCLUDED
