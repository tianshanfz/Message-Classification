#ifndef DATALEARNER_H_INCLUDED
#define DATALEARNER_H_INCLUDED

class DataLearner
{
    public:
    DataLearner();
    ~DataLearner();
    int ExecuteLearn();

    double GetThetaWordjky0(int k){return theta_word_y0[k];}
    double GetThetaWordjky1(int k){return theta_word_y1[k];}

    double GetThetaAddrjky0(int k){return theta_addr_y0[k];}
    double GetThetaAddrjky1(int k){return theta_addr_y1[k];}
    double GetThetaY1(){return theta_y;}
    double GetThetaY0(){return 1-theta_y;}
    int PrintParameters();

protected:
    int CalWordParameters();
    int CalAddrParameters();
    double* theta_word_y1;//Q(j|y=1)
    double* theta_word_y0;//Q(j|y=0)
     double* theta_addr_y1;//Q(j|y=1)
    double* theta_addr_y0;//Q(j|y=0)
    double  theta_y;


};

#endif // DATALEARNER_H_INCLUDED
