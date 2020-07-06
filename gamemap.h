#ifndef GAMEMAP_H
#define GAMEMAP_H
#include "ETypeVeg.h"
#include "vegetation.h"
#include "onemap.h"
#include <QVector>
struct coordinates2D
{
    qint32 len;
    qint32 wid;
    EtypeVeg paintType;
    coordinates2D *tempCoor;
    friend bool operator<(const coordinates2D la, const coordinates2D ra);
};

class GameMap
{
    QVector<QVector<OneMap>> map;

public:
    GameMap();




    const QColor& outColor(qint32 i, qint32 t);
    qint32 getLength();
    qint32 getWidth();

    OneMap* getPl_Up(qint32 i, qint32 t);
    OneMap* getPl_UpRt(qint32 i, qint32 t);
    OneMap* getPl_Rt(qint32 i, qint32 t);
    OneMap* getPl_DnRt(qint32 i, qint32 t);
    OneMap* getPl_Dn(qint32 i, qint32 t);
    OneMap* getPl_DnLt(qint32 i, qint32 t);
    OneMap* getPl_Lt(qint32 i, qint32 t);
    OneMap* getPl_UpLt(qint32 i, qint32 t);

    bool randomEvent();
    bool createGameMap(qint32 in_length, qint32 in_width);

    OneMap& operator()(const int i, const int t);

protected:
    coordinates2D *findNextEl(const coordinates2D &nowCoor, qint32 rNumber);
    bool findTwoEl(coordinates2D nowCoor);

};

#endif // GAMEMAP_H
