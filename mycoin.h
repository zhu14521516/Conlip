#ifndef MYCOIN_H
#define MYCOIN_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include"QPushButton"
#include"QTimer"
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    // explicit MyCoin(QWidget *parent = nullptr);
    //参数显示传进来的是金币还是银币
    MyCoin(QString btnImg);
    //金币的属性
    int posX;
    int posY;
    bool  flag;
    //改变标志的方法
    void chageFlag();
    QTimer *timer1;
    QTimer *timer2;
    int min=1;
    int max=8;
    //执行动画 标志
    bool isAnimation=false;
    //重写按下和释放
    void mousePressEvent(QMouseEvent *);
    //判断是否胜利
    bool isWin=false;
signals:

};

#endif // MYCOIN_H
