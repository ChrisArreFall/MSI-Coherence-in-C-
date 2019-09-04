#include "mainwindow.h"
#include "ui_mainwindow.h"


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Init all processors
    cpu0.init(0);
    cpu1.init(1);
    cpu2.init(2);
    cpu3.init(3);
    //Init all threads
    threadCPU0 = new ThreadCPU(this);
    threadCPU1 = new ThreadCPU(this);
    threadCPU2 = new ThreadCPU(this);
    threadCPU3 = new ThreadCPU(this);
    //Assign a processor to each thread
    threadCPU0->cpu=&cpu0;
    threadCPU1->cpu=&cpu1;
    threadCPU2->cpu=&cpu2;
    threadCPU3->cpu=&cpu3;
    //Reference main memory to CPUs
    threadCPU0->memory=&memory;
    threadCPU1->memory=&memory;
    threadCPU2->memory=&memory;
    threadCPU3->memory=&memory;
    //Reference mutex
    threadCPU0->mutex=&mutex;
    threadCPU1->mutex=&mutex;
    threadCPU2->mutex=&mutex;
    threadCPU3->mutex=&mutex;
    //Reference cache bus to CPUs
    threadCPU0->busCache=&busCache;
    threadCPU1->busCache=&busCache;
    threadCPU2->busCache=&busCache;
    threadCPU3->busCache=&busCache;
    //processor state (general)
    threadCPU0->state=&state;
    threadCPU1->state=&state;
    threadCPU2->state=&state;
    threadCPU3->state=&state;
    //start processors
    threadCPU0->start();
    //threadCPU1->start();
    //threadCPU2->start();
    //threadCPU3->start();
    connect(threadCPU0,&ThreadCPU::output,[&](string outputCPU,string outputCache){
        ui->textCPU0->append(QString::fromStdString(outputCPU));
        //ui->textCache0->setText(QString::fromStdString(outputCache));
    });
    connect(threadCPU1,&ThreadCPU::output,[&](string outputCPU,string outputCache){
        ui->textCPU1->append(QString::fromStdString(outputCPU));
        //ui->textCache1->setText(QString::fromStdString(outputCache));
    });
    connect(threadCPU2,&ThreadCPU::output,[&](string outputCPU,string outputCache){
        ui->textCPU2->append(QString::fromStdString(outputCPU));
        //ui->textCache2->setText(QString::fromStdString(outputCache));
    });
    connect(threadCPU3,&ThreadCPU::output,[&](string outputCPU,string outputCache){
        ui->textCPU3->append(QString::fromStdString(outputCPU));
        //ui->textCache3->setText(QString::fromStdString(outputCache));
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}





