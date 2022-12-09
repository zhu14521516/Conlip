#include "mainscence.h"

#include <QApplication>

#include"QDebug"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("yoyo");
    a.setApplicationName("yootu_pos");
    MainScence w;
    w.show();

//    //测试关卡数据
//    dataConfig config;
//    for(int i=0;i<4;i++){
//        for(int j=0;j<4;j++){
//            qDebug()<<config.mData[1][i][j];        }
//    }
    int e=a.exec();
    qDebug()<<"aa"<<e;
    return e;
}
