#include "vegetation.h"

std::array<typeVeg, (int)EtypeVeg::MAX_TYPE_VEG> Vegetation::VType
{
    typeVeg{"Water", QColor(38, 75, 171, 255)},
    typeVeg{"Wasteland", QColor(254, 205 , 137 , 255)},
    typeVeg{"Small vegetation", QColor(153, 240, 168, 255)},
    typeVeg{"Medium vegetation", QColor(101, 173, 113, 255)},
    typeVeg{"Large vegetation", QColor(67, 115, 75, 255)}
};

Vegetation::Vegetation(EtypeVeg inType)
    :
      thisType(inType),
      VColor(VType[(int)inType].color)
{
}

EtypeVeg Vegetation::getType()
{
    return thisType;
}

const QColor& Vegetation::getColor()
{
    //if ((int)thisType >= 0 && (int)thisType < (int)EtypeVeg::MAX_TYPE_VEG)
        return VType[(int)thisType].color;
    //else
    //    return QColor(243, 118, 245, 255);
}

bool Vegetation::setType(EtypeVeg inType)
{
    thisType = inType;
    return true;
}

bool Vegetation::typeUp()
{
    if (thisType < EtypeVeg::LARGE_VEGETATION)
    {
        thisType = static_cast<EtypeVeg>(static_cast<int>(thisType) + 1);
        return true;
    }
    else
        return false;
}

bool Vegetation::typeUnder()
{
    if (thisType > EtypeVeg::WATER)
    {
        thisType = static_cast<EtypeVeg>(static_cast<int>(thisType) - 1);
        return true;
    }
    else
        return false;
}

