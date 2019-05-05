#ifndef plots_H
#define plots_H

#include <QDialog>

namespace Ui {
class plots;
}

class plots : public QDialog
{
    Q_OBJECT

public:
    explicit plots(QWidget *parent = 0);
    ~plots();
    void plotPathLoss(double *Data, int TxIndex_i,  int TxIndex_j, int rows, int columns, int totalArea);

private:
    Ui::plots *ui;
};

#endif // plots_H
