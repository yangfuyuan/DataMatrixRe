#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("DataMatrixRecognition");
    ui->openBtn->setEnabled(true);

    reg_time = 0;
    ui->XlineEdit->setText("0");
    ui->YlineEdit->setText("0");
    ui->AlineEdit->setText("0");
    ui->ElineEdit->setText("00000000");
    ui->timelineEdit->setText("0");

    timer   = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));  // 时间到，读取当前摄像头信息
    connect(ui->openBtn, SIGNAL(clicked()), this, SLOT(openCamara()));
    connect(ui->closeBtn, SIGNAL(clicked()), this, SLOT(closeCamara()));


}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;

}

void MainWindow::closeEvent(QCloseEvent *e)
{
    Q_UNUSED(e)
    closeCamara();

}

void MainWindow::openCamara()
{
    Camera.setCaptureSize(320, 240);
    Camera.setFormat(raspicam::RASPICAM_FORMAT_RGB);
    if ( !Camera.open()) {qDebug()<<"Error opening camera";return;}
    timer->start(40);
    ui->openBtn->setEnabled(false);

}
void MainWindow::readFarme()
{
     QTime t;
     t.start();
     Camera.grab();
     unsigned char *data=new unsigned char[  Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB )];
     Camera.retrieve ( data,raspicam::RASPICAM_FORMAT_IGNORE );//get camera image

     dmtx_decoded_t *result = dmtx_decode(data,Camera.getWidth(),Camera.getHeight(), DmtxPack24bppRGB, 33);
     if(result != NULL){

         if(result->data != NULL){
             std::string message = (const char*)result->data;
             reg_time = t.elapsed();
             ui->XlineEdit->setText(tr("%1").arg(result->x));
             ui->YlineEdit->setText(tr("%1").arg(result->y));
             ui->AlineEdit->setText(tr("%1").arg(result->angle));
             ui->ElineEdit->setText(QString::fromLocal8Bit(message.c_str()));
             ui->timelineEdit->setText(tr("%1").arg(reg_time));
         }


         dmtx_decoded_destroy(result);
     }



    QImage image = QImage(data, Camera.getWidth(), Camera.getHeight(), QImage::Format_RGB888);//.rgbSwapped();
    ui->CameraView->setPixmap(QPixmap::fromImage(image));  // 将图片显示到label上
    delete data;

}




void MainWindow::closeCamara()
{
    timer->stop();         // 停止读取数据。
    if(Camera.isOpened())
       Camera.release();

    ui->CameraView->clear();
    ui->openBtn->setEnabled(true);
}


