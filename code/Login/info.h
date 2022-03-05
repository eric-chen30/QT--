#ifndef INFO_H
#define INFO_H

#include <QWidget>
namespace Ui {
class info;
}

class info : public QWidget
{
    Q_OBJECT

public:
    explicit info(QWidget *parent = 0);
    ~info();

signals:    //信号
    //车主注册
    void registeredcarsignal();
    //即时呼叫
    void instantCall();
    //预约呼叫
    void appointCall();

private slots:

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_3_clicked();

    void acceptLogin();

private:
    Ui::info *ui;
};

#endif // INFO_H
