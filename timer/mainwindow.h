#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QProcess>
#include <QMessageBox>
#include <QMainWindow>

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
    void on_readoutput();
    void on_readerror();
    void on_middleware_clicked();

    void on_timer_clicked();

    void on_subscriber_clicked();

private:
    Ui::MainWindow *ui;
    QProcess *cmd;
};

#endif // MAINWINDOW_H
