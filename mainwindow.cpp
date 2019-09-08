#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>

#include "iostream"


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    //QObject::connect(&thread,SIGNAL(signalGUI(const QString&)),lineEdit,SLOT(setText(const QString&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::setText(const QString &string)
{
    QChar id = string.at(0);
    QChar type = string.at(1);
    if(type=='0'){
        if(id=='0'){
            ui->textCache0->setText(string.mid(2));
        }
        else if(id=='1'){
            ui->textCache1->setText(string.mid(2));
        }
        else if(id=='2'){
            ui->textCache2->setText(string.mid(2));
        }
        else if (id=='3') {
            ui->textCache3->setText(string.mid(2));
        }
    }
    else if(type =='1'){
        if(id=='0'){
            ui->textCPU0->append(string.mid(2));
        }
        else if(id=='1'){
            ui->textCPU1->append(string.mid(2));
        }
        else if(id=='2'){
            ui->textCPU2->append(string.mid(2));
        }
        else if (id=='3') {
            ui->textCPU3->append(string.mid(2));
        }
    }
    else{
        ui->textMemory->setText(string);
    }


}



void MainWindow::on_meanSlider_sliderMoved(int position)
{
    emit signalMean(position);
}

void MainWindow::on_varSlider_sliderMoved(int position)
{
    emit signalVar(position);
}

void MainWindow::on_startButton_clicked()
{
    cout<<"Hello"<<endl;
    emit signalStatus();
}
