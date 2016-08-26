#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//typedef int (*CallbackResult)(dmtx_decoded_t *);  //声明回调函数


#include <QtGlobal>
#include <QMainWindow>
#include <QImage>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QTime>


#include "libdmtx/detector.h"

#include <raspicam/raspicam.h>
#include <raspicam/raspicamtypes.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();





private slots:
    void openCamara();      // 打开摄像头
    void readFarme();       // 读取当前帧信息
    void closeCamara();     // 关闭摄像头。

private:
    Ui::MainWindow *ui;
    QTimer    *timer;

    int reg_time;
    raspicam::RaspiCam Camera; //Cmaera object


protected:
    void closeEvent(QCloseEvent *e);



};


#endif // MAINWINDOW_H
