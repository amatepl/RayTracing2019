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

private:
    Ui::plots *ui;
};

#endif // plots_H
