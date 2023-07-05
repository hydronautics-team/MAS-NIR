#ifndef CS_ROV_H_
#define CS_ROV_H_

#include "rov_model.h"
#include <QThread>
#include <QSettings>
#include "math.h"
#include <qmath.h>
#include <QTime>
#include <QDebug>

const QString ConfigFile = "protocols.conf";
const QString XI = "x";
const QString KI = "k";


class CS_ROV : public QObject
{
    Q_OBJECT
public:
    CS_ROV(QObject * parent = nullptr);

public slots:
    void tick();

public:

protected:
    void readDataFromPult();
    void regulators();
    void BFS_DRK(double Upsi, double Uteta, double Ugamma, double Ux, double Uy, double Uz);
    void writeDataToModel();
    ROV_Model model;
    QTimer timer;
    bool modellingFlag = true;
    char coeff;
};
#endif // CS_ROV_H_
