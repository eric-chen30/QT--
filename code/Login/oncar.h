#ifndef ONCAR_H
#define ONCAR_H

#include <QMainWindow>

namespace Ui {
class oncar;
}

class oncar : public QMainWindow
{
    Q_OBJECT

public:
    explicit oncar(QWidget *parent = 0);
    ~oncar();

    static double distance;

    QTimer *timer; // 计时器

signals:
    void closeAppinfo();

private slots:
    void acceptgetOnCar();
    void acceptCurrentPlace();
    void updateDist();      // 定时器绑定的更新函数

private:
    Ui::oncar *ui;
};

#endif // ONCAR_H
