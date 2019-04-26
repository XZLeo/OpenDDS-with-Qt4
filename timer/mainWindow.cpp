#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>

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
    cmd->write("source /home/leo/OpenDDS-3.13.2/setenv.sh\n"); //一定记得\n
    ui->textEdit->append("环境变量已设置");
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
               "-ORBEndpoint iiop://localhost:12345\n"); //一定要加\n!
    ui->textEdit->append("DCPSInfoRepo starts.");
}


void MainWindow::on_timer_clicked()
{
    ui->textEdit->clear();
    cmd->write("/home/leo/OpenDDS-3.13.2/Timer/publisher"); //DCPSInforepo启动会不会阻塞publisher？这里用的是一个cmd？改用start会不会就能解决？
    ui->textEdit->append("Timer starts.");
}

void MainWindow::on_subscriber_clicked()
{
    ui->textEdit->clear();
    cmd->write("/home/leo/OpenDDS-3.13.2/Timer/subscriber");
    ui->textEdit->append("Accepted.");

}
