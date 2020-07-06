#include "gamemap.h"
#include <random>
#include <ctime>
#include <array>
#include <set>
#include <QColor>
#include <QDebug>
#include "ETypeVeg.h"

bool operator<(const coordinates2D la, const coordinates2D ra)
{
    return (la.len + la.wid) < (ra.len + ra.wid);
}

GameMap::GameMap()
{

}

qint32 GameMap::getLength()
{
    qint32 test = 0;
    return map.size();
}
qint32 GameMap::getWidth()
{
    if (!map.empty())
        return map[0].size();
    else
        return 0;
}

OneMap* GameMap::getPl_Up(qint32 i, qint32 t)
{
    if (i == 0)
        return nullptr;
    return &map[i - 1][t];
}
OneMap* GameMap::getPl_UpRt(qint32 i, qint32 t)
{
    if ((i == 0) && (t == map[i].size() - 1))
        return nullptr;
    return &map[i - 1][t + 1];
}
OneMap* GameMap::getPl_Rt(qint32 i, qint32 t)
{
    if (t == map[i].size() - 1)
        return nullptr;
    return &map[i][t + 1];
}
OneMap* GameMap::getPl_DnRt(qint32 i, qint32 t)
{
    if ((i == map.size() - 1) || (t == map[i].size() - 1))
        return nullptr;
    return &map[i + 1][t + 1];
}
OneMap* GameMap::getPl_Dn(qint32 i, qint32 t)
{
    if (i == map.size() - 1)
        return nullptr;
    return &map[i + 1][t];
}
OneMap* GameMap::getPl_DnLt(qint32 i, qint32 t)
{
    if ((i == map.size() - 1) || (t == 0))
        return nullptr;
    return &map[i + 1][t - 1];
}
OneMap* GameMap::getPl_Lt(qint32 i, qint32 t)
{
    if (t == 0)
        return nullptr;
    return &map[i][t - 1];
}
OneMap* GameMap::getPl_UpLt(qint32 i, qint32 t)
{
    if ((i == 0) || (t == 0))
        return nullptr;
    return &map[i - 1][t];
}

bool GameMap::createGameMap(qint32 in_length, qint32 in_width)
{
    //create start map
    map.resize(in_width);
    std::mt19937 randomNumber(time(0));
    for (qint32 i = 0; i < in_width; ++i)
    {
        map[i].resize(in_length);
        for (qint32 t = 0; t < in_length; ++t)
        {
            map[i][t].setType((EtypeVeg)((int)EtypeVeg::MAX_TYPE_VEG));
        }
    }

    //
    //create randomMap
    //


    //random keys for each type of land
    static std::array<qint32, (int)EtypeVeg::MAX_TYPE_VEG> rKey
    {
        10, //WATER
        20, //WASTERLAND
        56, //SMALL_VEGETATION
        22, //MEDIUM_VEGETATION
        23 //LARGE_VEGETATIOM
    };

    // density of the same type,
    qint32 densityType = 1;
    //the number of starting points
    qint32 countPoint = map.size() * map[0].size() * densityType / 10000 + 1;
    //list of starting points
    std::vector<coordinates2D> pointList;

    //create water


    for (qint32 i = 0; i < map.size(); ++i)
    {
        map[i][map[0].size() - 1].setType(EtypeVeg::WATER);
        map[i][0].setType(EtypeVeg::WATER);
    }
    for (qint32 t = 0; t < map[0].size(); ++t)
    {
        map[0][t].setType(EtypeVeg::WATER);
        map[map.size() - 1][t].setType(EtypeVeg::WATER);
    }



    //create countPoint
    for (qint32 i = 0; i < countPoint; ++i)
    {


        coordinates2D tempCoor;
        tempCoor.len = randomNumber() % (map.size() - 2) + 1;
        tempCoor.wid = randomNumber() % (map[0].size() - 2) + 1;
        tempCoor.paintType = EtypeVeg::LARGE_VEGETATION; //////////
        tempCoor.tempCoor = nullptr;
        //
        map[tempCoor.len][tempCoor.wid].setType(tempCoor.paintType);
        //
        pointList.push_back(tempCoor);

    }


    ////////////...............................................//

    int i = 0;
    while (i < 10)//!pointList.empty())
    {
        for (std::vector<coordinates2D>::iterator nowPoint = pointList.begin(); nowPoint != pointList.end(); ++nowPoint)
        {
            //if this point was already there
            if(nowPoint->tempCoor != nullptr &&
                    nowPoint->tempCoor->len == nowPoint->len &&
                    nowPoint->tempCoor->wid == nowPoint->wid)
            {
                qDebug() << "delete";
                pointList.erase(nowPoint);
                break;
            }
            coordinates2D* nextCoor = findNextEl(*nowPoint, randomNumber());
            qDebug() << "find " << nowPoint->len << " " << nowPoint->wid;
            //

            //if not find


            if (
                    nextCoor->len == nowPoint->len &&
                    nextCoor->wid == nowPoint->wid)
            {
                qDebug() << "not find";
                nowPoint->tempCoor = nextCoor;
                //run to find new place
            }/////////NEED DELETE
            else
            {
                qDebug() << "len " << nowPoint->len << " " << nextCoor->len;
                qDebug() << "wid " << nowPoint->wid << " " << nextCoor->wid;
                nowPoint->len = nextCoor->len;
                nowPoint->wid = nextCoor->wid;
                //////////
                if (map[nextCoor->len][nextCoor->wid].getType() != EtypeVeg::LARGE_VEGETATION)
                    map[nextCoor->len][nextCoor->wid].setType(EtypeVeg::MEDIUM_VEGETATION);
            }

            ///map[nowPoint->len][nowPoint->wid].setType(nowPoint->paintType);
            //





        }
        ++i;
    }









    return true;
}

OneMap& GameMap::operator()(const int i, const int t)
{
    return map[i][t];
}

coordinates2D *GameMap::findNextEl(const coordinates2D &nowCoor, qint32 rNumber)
{
    rNumber %= 4;
    qint32 endIterator = (rNumber - 1 + 4) % 4;
    while (endIterator != rNumber)
    {
        qDebug() << endIterator << " " << rNumber << " " << nowCoor.len << " " << nowCoor.wid;
        switch (rNumber)
        {
        case 0:
        {
            if (map[nowCoor.len - 1][nowCoor.wid].getType() == EtypeVeg::MAX_TYPE_VEG &&
                    findTwoEl(coordinates2D{nowCoor.len - 1, nowCoor.wid, nowCoor.paintType}))
                return new coordinates2D{nowCoor.len - 1, nowCoor.wid, nowCoor.paintType};

        }
        case 1:
        {
            if (map[nowCoor.len][nowCoor.wid + 1].getType() == EtypeVeg::MAX_TYPE_VEG &&
                    findTwoEl(coordinates2D{nowCoor.len, nowCoor.wid + 1, nowCoor.paintType}))
                return new coordinates2D{nowCoor.len, nowCoor.wid + 1, nowCoor.paintType};

        }
        case 2:
        {
            if (map[nowCoor.len + 1][nowCoor.wid].getType() == EtypeVeg::MAX_TYPE_VEG &&
                    findTwoEl(coordinates2D{nowCoor.len + 1, nowCoor.wid, nowCoor.paintType}))
                return new coordinates2D{nowCoor.len + 1, nowCoor.wid, nowCoor.paintType};

        }
        case 3:
        {
            if (map[nowCoor.len][nowCoor.wid - 1].getType() == EtypeVeg::MAX_TYPE_VEG &&
                    findTwoEl(coordinates2D{nowCoor.len, nowCoor.wid - 1, nowCoor.paintType}))
                return new coordinates2D{nowCoor.len, nowCoor.wid - 1, nowCoor.paintType};

        }
        }
        ++rNumber;
        rNumber %= 4;
    }
    qDebug() << "WTF";
    return new coordinates2D{nowCoor.len, nowCoor.wid};
}

bool GameMap::findTwoEl(coordinates2D nowCoor)
{
    //if endMap
    if (
            nowCoor.len == 0 || nowCoor.len == map.size() - 1 ||
            nowCoor.wid == 0 || nowCoor.wid == map[0].size() - 1)
        return false;

    qint32 nowFind = 0;
    if (getPl_UpLt(nowCoor.len, nowCoor.wid)->getType() == nowCoor.paintType) //1
        ++nowFind;
    if (getPl_Up(nowCoor.len, nowCoor.wid)->getType() == nowCoor.paintType) //2
        ++nowFind;
    if (getPl_UpRt(nowCoor.len, nowCoor.wid)->getType() == nowCoor.paintType) //3
        ++nowFind;
    if (getPl_Rt(nowCoor.len, nowCoor.wid)->getType() == nowCoor.paintType)//4
        ++nowFind;
    if (getPl_DnRt(nowCoor.len, nowCoor.wid)->getType() == nowCoor.paintType) //5
        ++nowFind;
    if (getPl_Dn(nowCoor.len, nowCoor.wid)->getType() == nowCoor.paintType)//6
        ++nowFind;
    if (getPl_DnLt(nowCoor.len, nowCoor.wid)->getType() == nowCoor.paintType) //7
        ++nowFind;
    if (getPl_Lt(nowCoor.len, nowCoor.wid)->getType() == nowCoor.paintType) //8
        ++nowFind;
    if (nowFind >= 2)
        return true;
    else
        return false;

}

