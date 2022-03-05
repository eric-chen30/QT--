#ifndef CARREGISTER_H
#define CARREGISTER_H

#include <QWidget>
namespace Ui {
class carRegister;
}

class carRegister : public QWidget
{
    Q_OBJECT

public:
    explicit carRegister(QWidget *parent = 0);
    ~carRegister();

signals:
    void registeredsignal2();


private slots:

    void on_toolButton_clicked();
    void acceptrecargister();

private:
    Ui::carRegister *ui;
};

#endif // CARREGISTER_H
