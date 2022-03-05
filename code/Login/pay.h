#ifndef PAY_H
#define PAY_H

#include <QMainWindow>

namespace Ui {
class pay;
}

class pay : public QMainWindow
{
    Q_OBJECT

public:
    explicit pay(QWidget *parent = 0);
    ~pay();

    static int orderId;

signals:
    void evaluationSignal();

private slots:
    void acceptPaySingal();

    void on_pushButton_clicked();

private:
    Ui::pay *ui;
};

#endif // PAY_H
