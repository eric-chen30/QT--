#ifndef TOREGISTER_H
#define TOREGISTER_H

#include <QWidget>
namespace Ui {
class toRegister;
}

class toRegister : public QWidget
{
    Q_OBJECT

public:
    explicit toRegister(QWidget *parent = 0);
    ~toRegister();

signals:
    void registeredsignal();

private slots:

    void acceptedregister();
    void on_toolButton_clicked();

private:
    Ui::toRegister *ui;
};

#endif // TOREGISTER_H
