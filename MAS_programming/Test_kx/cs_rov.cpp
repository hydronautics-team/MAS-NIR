#include "cs_rov.h"

CS_ROV::CS_ROV(QObject *parent)
{
    connect(&timer, &QTimer::timeout, this, &CS_ROV::tick);
    timer.start(10);
}

void CS_ROV::tick()
{
    readDataFromPult();
    regulators();
    BFS_DRK(X[65][0], X[85][0], X[75][0], X[105][0], X[115][0], X[95][0]);
    writeDataToModel();
}

void CS_ROV::readDataFromPult()
{
    X[51][0] = K[1]; //курс (в градусах), задаваемый через пульт
    X[52][0] = K[2]; //крен (в градусах), задаваемый через пульт
    X[53][0] = K[3]; //дифферент (в градусах), задаваемый через пульт
    X[54][0] = K[4]; //заданная с пульта маршевая скорость
    X[55][0] = K[5]; //заданная с пульта лаговая скорость
    X[56][0] = K[6]; //глубина, задаваемая через пульт


}

void CS_ROV::regulators()
{   //курс
    X[61][0] = X[51][0]-X[18][0];
    X[62][0] = K[10]*X[61][0];
    X[63][0] = K[9]*X[51][0];
    X[64][0] = K[11]*X[12][0];
    X[65][0] = X[62][0]+X[63][0]-X[64][0]; //Upsi

    //крен
    X[71][0] = X[52][0]-X[16][0];
    X[72][0] = K[12]*X[71][0];
    X[73][0] = K[9]*X[52][0];
    X[74][0] = K[13]*X[10][0];
    X[75][0] = X[72][0]+X[73][0]-X[74][0]; //Ugamma

    //дифферент
    X[81][0] = X[53][0]-X[17][0];
    X[82][0] = K[14]*X[81][0];
    X[83][0] = K[9]*X[53][0];
    X[84][0] = K[15]*X[11][0];
    X[85][0] = X[82][0]+X[83][0]-X[84][0]; //Utetta

    //глубина
    X[91][0] = X[56][0]-X[21][0];
    X[92][0] = K[16]*X[91][0];
    X[93][0] = K[9]*X[56][0];
    X[94][0] = K[17]*X[15][0];
    X[95][0] = X[92][0]+X[93][0]-X[94][0]; //Uz

    X[105][0] = K[4]*K[7]; //Ux
    X[115][0] = K[5]*K[8]; //Uy

    //X[66][0] = K[14]*X[52][0]; //Ux

}

void CS_ROV::BFS_DRK(double Upsi, double Uteta, double Ugamma, double Ux, double Uy, double Uz)
{
    X[70][0] = (K[20]*Ux + K[21]*Uy + K[22]*Uz + K[23]*Ugamma + K[24]*Uteta + K[25]*Upsi)*K[26];//U1
    X[80][0] = (K[30]*Ux + K[31]*Uy + K[32]*Uz + K[33]*Ugamma + K[34]*Uteta + K[35]*Upsi)*K[36];//U2
    X[90][0] = (K[40]*Ux + K[41]*Uy + K[42]*Uz + K[43]*Ugamma + K[44]*Uteta + K[45]*Upsi)*K[46];//U3
    X[100][0] = (K[50]*Ux + K[51]*Uy + K[52]*Uz + K[53]*Ugamma + K[54]*Uteta + K[55]*Upsi)*K[56];//U4
    X[110][0] = (K[60]*Ux + K[61]*Uy + K[62]*Uz + K[63]*Ugamma + K[64]*Uteta + K[65]*Upsi)*K[66];//U5
    X[120][0] = (K[70]*Ux + K[71]*Uy + K[72]*Uz + K[73]*Ugamma + K[74]*Uteta + K[75]*Upsi)*K[76];//U6
}

void CS_ROV::writeDataToModel()
{
    if (modellingFlag) {//режим модели
        model.tick(X[70][0], X[80][0], X[90][0], X[100][0], X[110][0], X[120][0], 0.01);
    }
}
