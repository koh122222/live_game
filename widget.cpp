#include <QPainter>
#include <random>
#include <QTimer>
#include <QRect>
#include <QPoint>
#include <array>
#include <ctime>
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    firstButton = new QPushButton("first Button", this);
    firstButton->setGeometry(QRect(QPoint(5, 5), QSize(100, 20)));


    connect(firstButton, SIGNAL (released()), this, SLOT(firstButtonPRESS()));
    randomButton = new QPushButton("random Button", this);
    randomButton->setGeometry(QRect(QPoint(115, 5), QSize(100, 20)));
    connect(randomButton, SIGNAL (released()), this, SLOT(random_buttonPRESS()));
    testLabel = new QLabel("label", this);
    testLabel->setGeometry((QRect(QPoint(300, 5), QSize(100, 20))));


    random_buttonPRESS();
}

void Widget::firstButtonPRESS()
{
    testLabel->setText("print_" + QString::number(testInt));
    ++testInt;
    this->update();
    outFlaf = true;
}

void Widget::random_buttonPRESS()
{
    testLabel->setText("random" + QString::number(testInt));
    ++testInt;
    qint32 lengthMap = 100;
    qint32 widthMap = 120;
    gameMap.createGameMap(lengthMap, widthMap);
}

void Widget::paintEvent(QPaintEvent *)
{
    //testLabel->setText("paint" + QString::number(testInt));
    //++testInt;
    qint32 lengthSize = 10;
    static std::array<QPoint, 4> oneOut
    {
        QPoint(5, 30),
        QPoint(5 + lengthSize, 30),
        QPoint(5 + lengthSize, 30 + lengthSize),
        QPoint(5, 30 + lengthSize)
    };


    QPainter painter(this);

    for (qint32 i = 0; i < gameMap.getLength(); ++i)
        for(qint32 t = 0; t < gameMap.getWidth(); ++t)
        {
            std::array<QPoint, 4> tempOut = oneOut;
            for(qint32 d = 0; d < 4; ++d)
            {
                tempOut[d].setX(tempOut[d].x() + i * lengthSize);
                tempOut[d].setY(tempOut[d].y() + t * lengthSize);
            }
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setPen(Qt::NoPen);
            painter.setBrush(gameMap(i, t).getColor());
            painter.save();
            painter.drawConvexPolygon(tempOut.begin(), 4);
            painter.restore();
        }
}

Widget::~Widget()
{
}

