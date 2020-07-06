#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QLabel>
#include "onemap.h"
#include "gamemap.h"

class Widget : public QWidget
{
    Q_OBJECT
    QPushButton *firstButton;
    QPushButton *randomButton;
    QLabel *testLabel;

    GameMap gameMap;

    quint64 testInt = 0;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:

    int outFlaf = false;

protected slots:
    void paintEvent(QPaintEvent *event) override;
    void random_buttonPRESS();
    void firstButtonPRESS();
};
#endif // WIDGET_H
