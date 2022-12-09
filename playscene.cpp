#include "playscene.h"
#include"QtDebug"
#include"QMenuBar"
#include"QPainter"
#include"mypushbutton.h"
#include"QTimer"
#include"QLabel"
#include"mycoin.h"
#include"dataconfig.h"
#include"QPropertyAnimation"
#include"QSound"
//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}
PlayScene::PlayScene(int levelNum){

    QString str=QString("进入了第 %1 关").arg(levelNum);
    qDebug()<<str;
    this->levelIndex=levelNum;
    //初始化游戏场景
    this->setFixedSize(320,588);

    this->setWindowIcon(QIcon(":/new/prefix1/Image/Coin0001.png"));
    this->setWindowTitle("翻金币场景");
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

    QSound * winSound= new QSound(":/new/prefix1/Image/LevelWinSound.wav",this);
    QSound * flipSound= new QSound(":/new/prefix1/Image/ConFlipSound.wav",this);
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

    //显示当前关卡数
    QLabel * label=new QLabel;
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(18);
    label->setFont(font);
    QString str2=QString("Level: %1").arg(this->levelIndex);
    label->setParent(this);
    label->setText(str2);



    //    label->setFixedSize();
    //    label->move(100,200);
    label->setGeometry(30,this->height()-50,200,50);
    //初始化每个关卡的二维数组
    dataConfig config;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++){
            this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
        }
    }

    //胜利图片的显示
    QLabel *winLabel=new QLabel;
    QPixmap temPix;
    temPix.load(":/new/prefix1/Image/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,temPix.width(),temPix.height());
    winLabel->setPixmap(temPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-temPix.width())*0.5,-temPix.height());


    //显示金币背景图
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++)
        {
            QPixmap pix=QPixmap(":/new/prefix1/Image/BoardNode.png");
            QLabel *label=new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57+i*50,200+j*50);
            //创建金币
            QString str;
            if(this->gameArray[i][j]==1)
            {
                str=":/new/prefix1/Image/Coin0001.png";
            }
            else
            {
                str=":/new/prefix1/Image/Coin0008.png";
            }
            MyCoin *coin=new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            //给金币属性赋值
            coin->posX=i;
            coin->posY=j;
            coin->flag=this->gameArray[i][j];
            coinBtn[i][j]=coin;
            //点击金币 进行翻转

            connect(coin,&MyCoin::clicked,[=](){

                coin->chageFlag();
                flipSound->play();
                this->gameArray[i][j]=this->gameArray[i][j]==0?1:0;
                //翻转周围的金币
                //翻转右侧的金币
                QTimer::singleShot(300,this,[=](){
                    if(coin->posX+1<=3)
                    {
                        coinBtn[coin->posX+1][coin->posY]->chageFlag();
                        this->gameArray[coin->posX+1][coin->posY]=this->gameArray[coin->posX+1][coin->posY]==0?1:0;

                    }
                    //翻转左侧的金币
                    if(coin->posX-1>=0)
                    {
                        coinBtn[coin->posX-1][coin->posY]->chageFlag();
                        this->gameArray[coin->posX-1][coin->posY]=this->gameArray[coin->posX-1][coin->posY]==0?1:0;

                    }

                    if(coin->posY+1<=3)
                    {
                        coinBtn[coin->posX][coin->posY+1]->chageFlag();
                        this->gameArray[coin->posX][coin->posY+1]=this->gameArray[coin->posX][coin->posY+1]==0?1:0;

                    }
                    if(coin->posY-1>=0)
                    {
                        coinBtn[coin->posX][coin->posY-1]->chageFlag();
                        this->gameArray[coin->posX][coin->posY-1]=this->gameArray[coin->posX][coin->posY-1]==0?1:0;

                    }
                    //判断是否胜利
                    this->iswin=true;
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(coinBtn[i][j]->flag==false)
                            {
                                this->iswin=false;
                                break;
                            }
                        }
                    }
                    if(this->iswin==true)
                    {
                        qDebug()<<"游戏胜利";
                        winSound->play();
                        //将所有按钮的胜利标志改为true
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                coinBtn[i][j]->isWin=true;

                            }
                        }
                        //将胜利图片砸下来
                        QPropertyAnimation *animation=new QPropertyAnimation(winLabel,"geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //设置开始位置
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        //设置结束位置
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));

                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //动画开始
                        animation->start();
                    }
                });

            });
        }
    }

}
void PlayScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/new/prefix1/Image/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //画背景上图标
    pix.load(":/new/prefix1/Image/Title.png");
    //进行缩放
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);



}

