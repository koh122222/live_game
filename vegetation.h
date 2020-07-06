#ifndef VEGETATION_H
#define VEGETATION_H
#include <array>
#include <QString>
#include <QColor>
#include "ETypeVeg.h"

struct typeVeg
{
   QString nameType;
   QColor color;
};

class Vegetation
{
protected:
    EtypeVeg thisType;
    quint32 nowPower = 0;
    quint32 maxPower = 5;
    QColor VColor;

public:
    Vegetation(EtypeVeg inType);
    static std::array<typeVeg, (int)EtypeVeg::MAX_TYPE_VEG> VType;
    EtypeVeg getType();
    const QColor& getColor();
    bool setType(EtypeVeg inType);
    bool typeUp();
    bool typeUnder();


};

#endif // VEGETATION_H
//add in ONEMAP!!!
