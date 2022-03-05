#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

signals:
    void registersignal();
    void loginsignal();

private slots:
    void on_toolButton_2_clicked();
    void on_toolButton_clicked();
    void acceptedlogin();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
