#ifndef HELP_H
#define HELP_H

#include <QDialog>

namespace Ui {
class help;
}

class help : public QDialog
{
    Q_OBJECT

public:
    explicit help(QWidget *parent = 0);
    ~help();

private:
    Ui::help *ui;
};

#endif // HELP_H
