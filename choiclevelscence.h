#ifndef CHOICLEVELSCENCE_H
#define CHOICLEVELSCENCE_H

#include <QMainWindow>
#include <QWidget>
#include"playscene.h"
class ChoicLevelScence : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChoicLevelScence(QWidget *parent = nullptr);

    //重写绘图事件
    void paintEvent(QPaintEvent *);
    //创建游戏界面指针
     PlayScene *play=NULL;
signals:
    //写一个自定义信号，告诉主场景 点击返回
    void chooseScenceBack();


};

#endif // CHOICLEVELSCENCE_H
