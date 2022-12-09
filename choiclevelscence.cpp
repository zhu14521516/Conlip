#include "choiclevelscence.h"
#include"QMenuBar"
#include"QPainter"
#include"mypushbutton.h"
#include"QLabel"
#include"QDebug"
#include"QTimer"
#include"QSound"
ChoicLevelScence::ChoicLevelScence(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/new/prefix1/Image/Coin0001.png"));
    //设置标题
    this->setWindowTitle("选择关卡场景");
    //创建菜单栏
    QMenuBar* bar=menuBar();
    setMenuBar(bar);
    //创建开始菜单
    QMenu *startMenu=bar->addMenu("开始");
    //创建退出菜单项
    QAction *quitAction=startMenu->addAction("退出");
    //点击退出 实现退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    QSound * chooseSound= new QSound(":/new/prefix1/Image/TapButtonSound.wav",this);
     QSound * backSound= new QSound(":/new/prefix1/Image/BackButtonSound.wav",this);

    //返回按钮
    MyPushButton *backbtn=new MyPushButton(":/new/prefix1/Image/BackButton.png",":/new/prefix1/Image/BackButtonSelected.png");
    backbtn->setParent(this);
    backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());
    connect(backbtn,&MyPushButton::clicked,[=](){

        backSound->play();
        QTimer::singleShot(500,this,[=](){
            emit this->chooseScenceBack();

        });

    });
    //创建选择关卡的按钮
    for(int i=0;i<20;i++){

        MyPushButton *menubtn=new MyPushButton(":/new/prefix1/Image/LevelIcon.png");
        menubtn->setParent(this);
        menubtn->move(i%4*70+25,i/4*70+130);
        //监听每个按钮的点击事件
        connect(menubtn,&MyPushButton::clicked,[=](){
            //播放选择关卡的音效
            chooseSound->play();
            QString str=QString("您选择的是第 %1 关").arg(i+1);
            qDebug()<<str;


            this->hide();
            play =new PlayScene(i+1);//创建游戏场景
            //设置游戏场景的初始位置
            play->setGeometry(this->geometry());
            play->show();//显示游戏场景

            connect(play,&PlayScene::chooseScenceBack,[=](){
                this->setGeometry(play->geometry());

                this->show();
                delete play;
                play=NULL;
            });
        });
        QLabel *label=new QLabel;
        label->setParent(this);
        label->setFixedSize(menubtn->width(),menubtn->height());
        label->setText(QString::number(i+1));
        label->move(i%4*70+25,i/4*70+130);
        //设置label上的文字对齐方式
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        //设置让鼠标进行穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

    }
}
void ChoicLevelScence::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/new/prefix1/Image/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //画背景上图标
    pix.load(":/new/prefix1/Image/Title.png");
    //进行缩放

    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);



}
