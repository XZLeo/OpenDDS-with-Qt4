#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cmd = new QProcess(this);
    connect(cmd, SIGNAL(readyReadStandardOutput()),this,SLOT(on_readoutput()));
    connect(cmd,SIGNAL(readyReadStandardOutput()),this, SLOT(on_readoutput()));

    cmd->start("bash");
    cmd->waitForStarted();
    cmd->write("/home/leo/OpenDDS-3.13.2/bin/setenv.sh"+'\n');

}

MainWindow::~MainWindow()
{
    if(cmd)
    {
        cmd->terminate();
        cmd->waitForFinished();
    }
    delete ui;
}

void MainWindow::on_readoutput(){
    ui->textEdit->append(cmd->readAllStandardOutput().data());
}

void MainWindow::on_readerror(){
    QMessageBox::information(0,"Error",cmd->readAllStandardError().data());
}

void MainWindow::on_middleware_clicked()
{
    ui->textEdit->clear();
    cmd->write("/home/leo/OpenDDS-3.13.2/bin/DCPSInfoRepo"
               "-ORBEndpoint iiop://localhost:12345"+'\n'); \\一定要加\n!
    /*
    QProcess process(this);
    process.setProgram("/home/leo/OPenDDS-3.13.2/bin/DCPSInfoRepo");
    QStringList argument;
    argument<<"-ORBEndpoint iiop://localhost:12345";
    process.setArguments(argument);
    process.start();
    process.waitForStarted();
    QString temp = "DCPS Information Repository Starts";
    ui->textEdit->setText(temp);*/
}


























/*
void MainWindow::on_pushButton_clicked()
{
    ui->textEdit->clear();
    QProcess process(this);
    process.setProgram("/home/leo/OPenDDS-3.13.2/bin/DCPSInfoRepo");
    QStringList argument;
    argument<<"-ORBEndpoint iiop://localhost:12345";
    process.setArguments(argument);
    process.start();
    process.waitForStarted();
    QString temp = "DCPS Information Repository Starts";
    ui->textEdit->setText(temp);
}

void MainWindow::on_pushButton_2_clicked()
{
    QProcess process(this);
    //process.setProgram("/home/leo/OpenDDS-3.13.2/Timer/publisher");
    process.start("bash");
    process.waitForStarted();
    QString temp = "Timer Starts";
    ui->textEdit->setText(temp);
    process.waitForFinished();
}



void MainWindow::on_pushButton_3_clicked()
{
    QProcess process(this);
    process.setProgram("/home/leo/OpenDDS-3.13.2/Timer/subscriber");
    process.start();
    process.waitForStarted();
    process.waitForReadyRead();
    QString temp = QString::fromLocal8Bit(process.readAllStandardOutput()); //关键是标准读入的数据是什么形式的
    ui->textEdit->setText(temp); //
}*/

