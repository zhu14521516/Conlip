#include "mycoin.h"
#include"QDebug"
//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{

//}
MyCoin::MyCoin(QString btnImg){



    QPixmap pix;
    bool ret=pix.load(btnImg);
    if(!ret){

        QString str=QString("图片 %1 加载失败").arg(btnImg);
        qDebug()<<str;
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    //初始化定时器对象
    timer1=new QTimer(this);
    timer2=new QTimer(this);


    connect(timer1,&QTimer::timeout,[=]()
    {
        QPixmap pix;
        QString str=QString(":/new/prefix1/Image/Coin000%1.png").arg(this->min++);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //如果翻完了
        if(this->min>this->max){
            this->min=1;
            isAnimation=false;//最开始动画
            timer1->stop();
        }
    });
    connect(timer2,&QTimer::timeout,[=]()
    {
        QPixmap pix;
        QString str=QString(":/new/prefix1/Image/Coin000%1.png").arg(this->max--);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //如果翻完了
        if(this->max<this->min){
            this->max=8;
            isAnimation=false;//最开始动画
            timer2->stop();
        }
    });
}
void MyCoin::chageFlag(){


    //如果是正面
    if(this->flag){
        //开始正面翻翻面的定时器
        timer1->start(30);
        isAnimation=true;//最开始动画
        this->flag=false;
    }
    //
    else
    {
        timer2->start(30);
        isAnimation=true;//最开始动画
        this->flag=true;
    }
}
void MyCoin::mousePressEvent(QMouseEvent *e){

    if(this->isAnimation||this->isWin)
    {

        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}
