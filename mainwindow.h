#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QLabel>
#include <QFont>
#include <QString>
#include <QDebug>
#include <QTextStream>
#include <QSocketNotifier>//Added for GPIO
#include<qfile.h>

//Linux related Headres
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <linux/i2c-dev.h> //needed for I2C
#include <sys/time.h>     // for gettimeofday()
#include <sys/types.h>
#include <linux/hdreg.h>
#include <sys/ioctl.h>
#include <linux/input.h> //Needed for rotary_encoder event detection

#include "qpaintdevice.h"
#include "qpainter.h"
#include "qpainterpath.h"
#include <QPainter>
#include <QRect>
#include <QBrush>
#include <QTextEdit>
#include<qtextcodec.h>
#include <qwidget.h>
#include<qboxlayout.h>
#include<QHBoxLayout>
#include <qpainter.h>
#include<qpainterpath.h>
#include<QGraphicsPathItem>
#include <qtimer.h>
#include <QDateTimeEdit> //Added for date and time edit





//Long Double to QString
#include <sstream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QGraphicsRectItem* gray_box = new QGraphicsRectItem(0,0,168,475);
         QPainterPath path;
          QPainterPath path2;
          QBrush brush;

          //Encode Related
          int fd_Encoder,fd_encbutton;
          QSocketNotifier *encodernotifier,*encbuttonnotifier;
          QFile encodervalue,encbuttonvalue;

          //QDate *avDate =new QDate;
         // QTime *avTime =new QTime;
          QString Date_s,Time_s;
          QFont Date_Time;
           QGraphicsTextItem * AV_Date = new QGraphicsTextItem;
           QGraphicsTextItem * AV_Time = new QGraphicsTextItem;

    public slots:
          void showDateTime();
          void updateDateTime(int code,int value);
          void encoderSlot(void);
          void encbuttonSlot();
          void foo();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
