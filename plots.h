#ifndef plots_H
#define plots_H

#include <QDialog>
#include "room.h"

namespace Ui {
class plots;
}

class room;

class plots : public QDialog
{
    Q_OBJECT

public:
    explicit plots(QWidget *parent = 0);
    ~plots();
    void plotPathLoss(room *scene);
    int linreg(int n, QVector<double> x, QVector<double> y, double* m, double* b, double* r);
    double findStandardDeviation(QVector<double> array);

private:
    Ui::plots *ui;
};

#endif // plots_H
