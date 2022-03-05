#ifndef ACCEPTED_H
#define ACCEPTED_H

#include <QDialog>

namespace Ui {
class accepted;
}

class accepted : public QDialog
{
    Q_OBJECT

public:
    explicit accepted(QWidget *parent = 0);
    ~accepted();

    static QString startingPlace;
    static QString destination;
    static QString carNumber;
    static QString carColor;
    static QString carType;
    static int currentDriverId;

signals:
    void getOnCar();
    void currentPlace();
    void paySingal();

private slots:

    void acceptReceiveSignal();

    void acceptReceiveSignal2();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    int flag;
    Ui::accepted *ui;
};

#endif // ACCEPTED_H
