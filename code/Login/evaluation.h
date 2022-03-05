#ifndef EVALUATION_H
#define EVALUATION_H
#include <QDialog>

namespace Ui {
class evaluation;
}

class evaluation : public QDialog
{
    Q_OBJECT

public:
    explicit evaluation(QWidget *parent = 0);
    ~evaluation();

private slots:

    void on_submit_clicked();  // 评价按钮
    void acceptEvaluationSignal();


private:
    Ui::evaluation *ui;
};

#endif // EVALUATION_H
