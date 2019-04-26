#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cmd = new QProcess(this);
    connect(cmd , SIGNAL(readyReadStandardOutput()) , this , SLOT(on_readoutput())); //readyReadStandardOutPut
    connect(cmd , SIGNAL(readyReadStandardError()) , this , SLOT(on_readerror())); //SIGNAL宏指令

    cmd->start("bash");
    cmd->waitForStarted();
    cmd->write("source /home/leo/OpenDDS-3.13.2/setenv.sh\n");
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

void MainWindow::on_readoutput()
{
    ui->textEdit->append(cmd->readAllStandardOutput().data());
}

void MainWindow::on_readerror()
{
    QMessageBox::information(0, "Error", cmd->readAllStandardError().data());
}



void MainWindow::on_pushButton_clicked()
{
    cmd->write(ui->lineEdit->text().toLocal8Bit() + '\n');  //读入lineedit的然后输入给写入cmd
    // cmd->write("/home/leo/OpenDDS-3.13.2/bin"
              //"/DCPSInfoRepo -ORBEndpoint iiop://localhost:12345\n"); //启动之后前端进程会阻塞（点了没反应）
} //Qt里写命令最后一定要有\n相当于回车，不然不会执行命令！！！！

//很多库没有，要配置环境那个变量,用setenv.sh
