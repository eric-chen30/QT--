#ifndef INSTANTCALL_H
#define INSTANTCALL_H

#include <QDialog>

namespace Ui {
class instantcall;
}

class instantcall : public QDialog
{
    Q_OBJECT

public:
    explicit instantcall(QWidget *parent = 0);
    ~instantcall();

    static QString startingPlace;
    static QString destination;
    static QString carNumber;
    static QString carColor;
    static QString carType;
    static QString userName;
    static int currentDriverId;

signals:
    void receiveSignal2();
    void waitingCar2();

private slots:
    void on_submit_clicked();
    void acceptInstantCall();

private:
    Ui::instantcall *ui;
};

#endif // INSTANTCALL_H
