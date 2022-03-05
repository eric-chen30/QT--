#ifndef APPINFO_H
#define APPINFO_H

#include <QWidget>

namespace Ui {
class appinfo;
}

class appinfo : public QWidget
{
    Q_OBJECT

private slots:
    void acceptWaitingCar();
    void acceptWaitingCar2();

public:
    explicit appinfo(QWidget *parent = 0);
    ~appinfo();

    Ui::appinfo *ui;
};

#endif // APPINFO_H
