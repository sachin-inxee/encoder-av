#include "mainwindow.h"
#include "ui_mainwindow.h"

QTextStream out(stdout);


//Special Debug Message function
#define DEBUG_ENABLE 1
#if DEBUG_ENABLE >0
#define DBG_BUF_LEN   512
static char DBG_BUFFER[DBG_BUF_LEN];

#define app_debug(FORMAT,...) {\
    memset(DBG_BUFFER, 0, DBG_BUF_LEN);\
    sprintf(DBG_BUFFER,FORMAT,##__VA_ARGS__); \
   out << DBG_BUFFER << endl;\
   }
#else
#define app_debug(FORMAT,...)
#endif

static int count=0;
static int datetimecounter=0,datetimeselectionindex=0;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);


    ui->graphicsView->setScene(scene);

    Date_Time.setPixelSize(30);    //30
    Date_Time.setBold(1);
    Date_Time.setFamily("Calibri");


ui->avDate->setMinimumDate(QDate::currentDate().addDays(-365));
ui->avDate->setMaximumDate(QDate::currentDate().addDays(365));

    AV_Date->setPos(50,100);
    AV_Date->setFont(Date_Time);
    AV_Date->setPlainText("3");
    AV_Date->setDefaultTextColor("BLACK");
   // AV_Date->setMinimumDate(QDate::currentDate().addDays(-365));
   // AV_Date->setMaximumDate(QDate::currentDate().addDays(365));
    AV_Time->setPos(50,198);
    AV_Time->setFont(Date_Time);
    AV_Time->setPlainText("3");
    AV_Time->setDefaultTextColor("BLACK");
    ui->avDateTime->hide();

    ui->avDateTime->setGeometry(0,30,300,40);
    ui->avDateTime->setMinimumDate(QDate::currentDate().addDays(-365));
    ui->avDateTime->setMaximumDate(QDate::currentDate().addDays(365));
    ui->avDateTime->setDisplayFormat("dd.MM.yyyy hh:mm.ss");
    ui->avDateTime->setTime(QTime::currentTime());
    ui->avDateTime->hide();




    const char *encoderpath="/dev/input/event1";
    const char *encoderbuttonpath ="/dev/input/event4";

    fd_Encoder = open(encoderpath, O_RDONLY | O_NONBLOCK);
    fd_encbutton=open(encoderbuttonpath, O_RDONLY | O_NONBLOCK);

       encodervalue.open(fd_Encoder,QFile::ReadOnly);
       encodernotifier = new QSocketNotifier(encodervalue.handle(), QSocketNotifier::Read);
       encodernotifier->setEnabled(true);
       connect(encodernotifier, SIGNAL(activated(int)), this, SLOT(encoderSlot()));


       encbuttonvalue.open(fd_encbutton,QFile::ReadOnly);
       encbuttonnotifier = new QSocketNotifier(encbuttonvalue.handle(), QSocketNotifier::Read);
       encbuttonnotifier->setEnabled(true);
       connect(encbuttonnotifier, SIGNAL(activated(int)), this, SLOT(encbuttonSlot()));

       app_debug("Application Started\n");

   /* QPalette p = ui->progressBar->palette();
          ui->progressBar->setGeometry(300,100,40,20);
          ui->progressBar->setValue(2);
          p.setColor(QPalette::Highlight, Qt::red);
          p.setColor(QPalette ::AlternateBase, Qt :: black );
          p.setColor(QPalette ::Background, Qt :: green );
          ui->progressBar->setPalette(p);
          ui->progressBar->show();

        QPalette time_p=ui->timeEdit->palette();
        time_p.setColor(QPalette :: Text,Qt :: darkCyan);
        ui->timeEdit->setPalette(time_p);
        ui->timeEdit->show();
        ui->timeEdit->setTime(QTime :: currentTime().addSecs(24600));
      // ui->timeEdit->setTime(QTime :: currentTime());
*/

       /*  time_p.setColor(QPalette :: Text,Qt :: blue);
         ui->dateEdit->setPalette(time_p);
         ui->dateEdit->show();
         // ui->dateEdit->setDate(QDate :: currentDate().addYears(1).addMonths(1).addDays(2));   // Calibrated to real Date
         ui->dateEdit->setDate(QDate :: currentDate());*/


/*
        QTimer *clock_Timer = new QTimer(this);
        connect(clock_Timer,SIGNAL(timeout()),this,SLOT(showDateTime()));
        clock_Timer->start(1000);
*/


//connect(ui->avDateTime, SIGNAL(dateChanged(QDate)), this, SLOT(foo()));



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: foo()
{
    app_debug("foo\n");
}

void MainWindow:: showDateTime()
{
// ui->timeEdit->setTime(QTime :: currentTime().addSecs(17400));
   // ui->timeEdit->setTime(QTime :: currentTime());
 //   ui->timeEdit->setTime(QTime :: currentTime().addSecs(24600));
    QTime time = QTime::currentTime();
    QDate date= QDate::currentDate();
    Date_s= date.toString("dd.MM.yyyy");
     // QString text = time.toString("hh:mm");

      Time_s=time.toString("hh:mm:ss");
      AV_Date->setPlainText(Date_s);
      AV_Time->setPlainText(Time_s);
      /*if ((time.second() % 2) == 0)
          text[2] = ' ';*/
      //display(text);

}

void MainWindow:: updateDateTime(int code,int value)
{
   /* QDateTimeEdit *dateEdit = new QDateTimeEdit(QDate::currentDate());
    dateEdit->setGeometry(0,30,300,40);
    dateEdit->setMinimumDate(QDate::currentDate().addDays(-365));
    dateEdit->setMaximumDate(QDate::currentDate().addDays(365));
    dateEdit->setDisplayFormat("dd.MM.yyyy hh:mm.ss");
    dateEdit->setCalendarPopup(1);
    dateEdit->show();*/

    /*
    ui->avDateTime->setGeometry(0,30,300,40);
    ui->avDateTime->setMinimumDate(QDate::currentDate().addDays(-365));
    ui->avDateTime->setMaximumDate(QDate::currentDate().addDays(365));
    ui->avDateTime->setDisplayFormat("dd.MM.yyyy hh:mm.ss");
    ui->avDateTime->setTime(QTime::currentTime());
    ui->avDateTime->show();
    */

   // ui->avDateTime->setCurrentSection(QDateTimeEdit::YearSection);
   // ui->avDateTime->setCurrentSectionIndex(value);
    //ui->avDateTime->HourSection=12;
  //  ui->avDateTime->setFocus();
  //  ui->avDateTime->show();
//ui->avDateTime->HourSection=12;
    switch(code)
    {
    case 28:if(value!=0)
        {
            if(datetimecounter>=6)
            {
                datetimecounter=0;
                datetimeselectionindex=0;
            }
        switch(datetimecounter)
        {
         case 0: ui->avDateTime->setCurrentSection(QDateTimeEdit::DaySection);
                ui->avDateTime->setSelectedSection(QDateTimeEdit::DaySection);
                // ui->avDateTime->setCurrentSectionIndex(datetimecounter);
                  ui->avDateTime->setFocus();
                  datetimeselectionindex=0;
                  ui->avDateTime->show();
            break;
        case 1: ui->avDateTime->setCurrentSection(QDateTimeEdit::MonthSection);
                 ui->avDateTime->setSelectedSection(QDateTimeEdit::MonthSection);
               // ui->avDateTime->setCurrentSectionIndex(datetimecounter);
                ui->avDateTime->setFocus();
                datetimeselectionindex=1;
               ui->avDateTime->show();
           break;
        case 2: ui->avDateTime->setCurrentSection(QDateTimeEdit::YearSection);
             ui->avDateTime->setSelectedSection(QDateTimeEdit::YearSection);
               // ui->avDateTime->setCurrentSectionIndex(datetimecounter);
                ui->avDateTime->setFocus();
                datetimeselectionindex=2;
                ui->avDateTime->show();
           break;
        case 3: ui->avDateTime->setCurrentSection(QDateTimeEdit::HourSection);
             ui->avDateTime->setSelectedSection(QDateTimeEdit::HourSection);
               // ui->avDateTime->setCurrentSectionIndex(datetimecounter);
                ui->avDateTime->setFocus();
                datetimeselectionindex=3;
                ui->avDateTime->show();
           break;
        case 4: ui->avDateTime->setCurrentSection(QDateTimeEdit::MinuteSection);
                ui->avDateTime->setSelectedSection(QDateTimeEdit::MinuteSection);
               // ui->avDateTime->setCurrentSectionIndex(datetimecounter);
                ui->avDateTime->setFocus();
                datetimeselectionindex=4;
                ui->avDateTime->show();
           break;
        case 5: ui->avDateTime->setCurrentSection(QDateTimeEdit::SecondSection);
                 ui->avDateTime->setSelectedSection(QDateTimeEdit::SecondSection);
                ui->avDateTime->setCurrentSectionIndex(datetimecounter);
                ui->avDateTime->setFocus();
                datetimeselectionindex=5;
                ui->avDateTime->show();
           break;
        }//end of switch
        datetimecounter++;

        }//End of if
        break;
     case 2:
         //switch(ui->avDateTime->currentSection())
        switch(datetimeselectionindex)
        {
        case 0: {
             QDate dated = QDate::currentDate();
             dated = dated.addDays(value);
             //ui->avDateTime->sets
             ui->avDateTime->show();
        }
             break;
            case 1:
        {
             QDate datem=QDate::currentDate();
             datem=datem.addMonths(value);
             ui->avDateTime->setDate((QDate)datem);
             ui->avDateTime->setDate(QDate::currentDate());
             ui->avDateTime->setTime(QTime::currentTime());
             //QKeyEvent event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier, QString("Up"),0, 0);
            // QApplication::postEvent(this, event);
            // emit Key = Qt::Key_Up;
             //emit k_output(Qt::Key_Up);
             ui->avDateTime->show();
             break;
        }

        }//End of switch

        break;
    }

}


void MainWindow::encoderSlot(void)
{

    struct input_event ev_encoder;

    QByteArray data = encodervalue.readAll();

    while (data.size() >= int(sizeof(input_event)))
            {
                memcpy(&ev_encoder, data.data(), sizeof(input_event));

                data.remove(0, int(sizeof(input_event)));
                if(EV_REL==ev_encoder.type)
                {
               app_debug("type:%d,code:%d,value:%d count:%d\n",ev_encoder.type,ev_encoder.code,ev_encoder.value,count++);
               //ToDO: Add Encoder Handling here
               updateDateTime(ev_encoder.code,ev_encoder.value);
                }//End of if
            }

}


void MainWindow::encbuttonSlot(void)
{

    struct input_event ev_encbutton;

    QByteArray data = encbuttonvalue.readAll();

    while (data.size() >= int(sizeof(input_event)))
            {
                memcpy(&ev_encbutton, data.data(), sizeof(input_event));

                data.remove(0, int(sizeof(input_event)));
                if(EV_KEY==ev_encbutton.type)
                {
               app_debug("type:%d,code:%d,value:%d datetimecounter:%d\n",ev_encbutton.type,ev_encbutton.code,ev_encbutton.value,datetimecounter+1);
                updateDateTime(ev_encbutton.code,ev_encbutton.value);
                }//End of if
            }

}
