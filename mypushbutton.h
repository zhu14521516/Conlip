#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
#include"QPushButton"
#include <QWidget>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
   // explicit MyPushButton(QWidget *parent = nullptr);
    //构造函数 参数1 正常i西安市的图片路径 参数2 按下后显示的图片路径
    MyPushButton(QString normalImg,QString pressImag="");
    //成员属性 保存用户传入的默认参数显示路径 以及按下后的显示路径
    QString normallImgPath;
    QString pressImgPath;
    void zoom1();
     void zoom2();
     //重写按钮 按下 释放事件
     void mousePressEvent(QMouseEvent *e);

     void mouseReleaseEvent(QMouseEvent *e);
signals:

};

#endif // MYPUSHBUTTON_H
