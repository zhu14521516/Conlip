#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include"mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
   // explicit PlayScene(QWidget *parent = nullptr);
PlayScene(int levelNum);
int levelIndex;//内部成员属性 记录所选的关卡
//重写绘图事件
 void paintEvent(QPaintEvent *);
 //二维数组维护每关的数据
 int gameArray[4][4];
 //二维数组维护
 MyCoin *coinBtn[4][4];
 //判断是否胜利
 bool iswin;
signals:
 //写一个自定义信号，告诉主场景 点击返回
 void chooseScenceBack();

};

#endif // PLAYSCENE_H
