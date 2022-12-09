#include "mainscence.h"
#include "ui_mainscence.h"
#include"QPainter"
#include"QPixmap"
#include"mypushbutton.h"
#include"QTimer"
#include"QSound"
#include <QMediaPlayer>
#include <QMediaPlaylist>
MainScence::MainScence(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScence)
{

    ui->setupUi(this);
    //配置主场景

    //设置固定大小
    setFixedSize(320,588);
    //设置图标
    setWindowIcon(QIcon(":/new/prefix1/Image/Coin0001.png"));
    //设置标题
    setWindowTitle("翻金币主场景");
    //退出按钮实现
    connect(ui->action,&QAction::triggered,[=](){

        this->close();

    });
    //准备开始按钮的音效
    QSound * startSound= new QSound(":/new/prefix1/Image/TapButtonSound.wav",this);
    QSound *undergroundSound=new QSound(":/new/prefix1/Image/myDouDZ.wav",this);
    undergroundSound->setLoops(-1);
    undergroundSound->play();
    startSound->play();
//    QMediaPlaylist *playList=new QMediaPlaylist(this);

//    playList->addMedia(QUrl(":/new/prefix1/Image/myDouDZ.wav"));
//    QMediaPlayer *player=new QMediaPlayer(this);
//    player->setVolume(60);
//    player->setPlaylist(playList);
//    player->play();

    //开始按钮
    MyPushButton *startBtn=new MyPushButton(":/new/prefix1/Image/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);
    //实例化选择关卡的场景
    chooseScene=new ChoicLevelScence;
    //监听选择关卡的返回按钮
    connect(chooseScene,&ChoicLevelScence::chooseScenceBack,this,[=](){
        QTimer::singleShot(500,this,[=](){
            this->setGeometry(chooseScene->geometry());
            chooseScene->hide();//隐藏选择关卡
            this->show();//显示主场景
        });

    });
    connect(startBtn,&MyPushButton::clicked,[=](){
        //播放开始音效
        startSound->play();
        startBtn->zoom1();
        startBtn->zoom2();

        //进入选择关卡的场景
        QTimer::singleShot(500,this,[=](){
            //设置chooseScence的产经位置
            chooseScene->setGeometry(this->geometry());
            //自身隐藏
            this->hide();
            //显示选择关卡场景
            chooseScene->show();

        });

    });
}

void MainScence::paintEvent(QPaintEvent *){

    QPainter painter(this);

    QPixmap pix;
    pix.load(":/new/prefix1/Image/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //画背景上图标
    pix.load(":/new/prefix1/Image/Title.png");
    //进行缩放
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}
MainScence::~MainScence()
{
    delete ui;
}

