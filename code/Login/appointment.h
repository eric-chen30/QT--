#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <QMainWindow>

namespace Ui {
class appointment;
}

class appointment : public QMainWindow
{
    Q_OBJECT

public:
    explicit appointment(QWidget *parent = 0);
    ~appointment();
    static QString startingPlace;
    static QString destination;
    static QString carNumber;
    static QString carColor;
    static QString carType;
    static QString userName;
    static int currentDriverId;

signals:
    void receiveSignal();
    void waitingCar();

private slots:
    void on_submit_clicked();
    void acceptappointCall();

private:
    Ui::appointment *ui;

};

#endif // APPOINTMENT_H
