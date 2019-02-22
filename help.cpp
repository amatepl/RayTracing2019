#include "help.h"
#include "ui_help.h"

help::help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::help)
{
    /*
     * We use an inherited QDialog for a popup window, which does not effect the other windows *help->show() allow movement, *help->open() blocks other windows from
     * interacting.
     */

    ui->setupUi(this);
}

help::~help()
{
    delete ui;
}
