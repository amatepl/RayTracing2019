#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IEEE80211g)
{
    ui->setupUi(this);   // basic Qt, arrow -> is the same as (ui*).setupUi()

    scene = new room(this);
    scene->setSceneRect(ui->graphicsView->rect());
       ui->graphicsView->setScene(scene);
       ui->graphicsView->ensureVisible(scene->sceneRect());

       ui->spinBoxPosX->setReadOnly(true);
       ui->spinBoxPosY->setReadOnly(true);
       ui->spinBoxPosX->setValue(cursor().pos().x());
       ui->spinBoxPosY->setValue(cursor().pos().y());
       configureSpinBox(ui->spinBoxPosX, -INT_MIN, +INT_MAX);
       configureSpinBox(ui->spinBoxPosX, -INT_MIN, +INT_MAX);
       QBrush greenBrush(Qt::green);
       QBrush blueBrush(Qt::blue);
       QPen outlinePen(Qt::black);
       outlinePen.setWidth(2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::configureSpinBox(QSpinBox *spinBox, int min, int max)const{
    spinBox->setMinimum(min);
    spinBox->setMaximum(max);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    QWidget::mouseMoveEvent(event);
}


void MainWindow::mousePressEvent(QMouseEvent *event){
    //onMouseEvent("lala", event->pos());
    QWidget::mousePressEvent(event);
}


void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    QWidget::mouseReleaseEvent(event);
}


void MainWindow::onMouseEvent(const QString &eventName, const QPoint &pos){
    statusBar()->showMessage(eventName);
    ui->spinBoxPosX->setValue(pos.x());
    ui->spinBoxPosY->setValue(pos.y());
}


void MainWindow::on_antena_clicked()
{   statusBar()->showMessage("Place the antena");
    scene->setAntenaType(0);
}


void MainWindow::on_receiver_clicked()
{   statusBar()->showMessage("Place the receiver");
    scene->setAntenaType(1);
}


void MainWindow::on_helpButton_clicked()
{
    scene_help = new help();
    scene_help->show();
}


void MainWindow::on_settingsButton_clicked()
{
    scene_settings = new settings();
    scene_settings->open();
}

void MainWindow::on_clearWorkspaceButton_clicked(){

    scene->clearAll();
    scene = new room(this);
    scene->setSceneRect(ui->graphicsView->rect());
       ui->graphicsView->setScene(scene);
       ui->graphicsView->ensureVisible(scene->sceneRect());

       ui->spinBoxPosX->setReadOnly(true);
       ui->spinBoxPosY->setReadOnly(true);
       ui->spinBoxPosX->setValue(cursor().pos().x());
       ui->spinBoxPosY->setValue(cursor().pos().y());
       ui->spinBoxResult->setValue(0);
       ui->powerResultSpinBox->setValue(0);
       ui->binaryResultsSpinBox->setValue(0);
}

void MainWindow::on_generateCoveragePushButton_clicked()
{   statusBar()->showMessage("Launch map coverage");

    if(scene->getTransmitter() != NULL){
        scene->readSettingsFile();
        cov = new coverage(scene->getAmountDiscret(), scene, this);

    }else{
        statusBar()->showMessage("Placing emettor is needed to generate coverage");
    }
}

void MainWindow::on_commandLinkButton_clicked()
{   statusBar()->showMessage("Launch Ray-Tracing");

    if(scene->getReceiver() != NULL || scene->getTransmitter() != NULL){
        ui->spinBoxResult->setValue(scene->distance()*2*pow(10, -2));

        scene->readSettingsFile();
        scene->launch_algo();

        ui->powerResultSpinBox->setValue(scene->getReceivedPower());
        if(scene->getBinaryDebit() > 0){ui->binaryResultsSpinBox->setValue(scene->getBinaryDebit());}


    }else{
        statusBar()->showMessage("Placing the emettor/receptor is requiered");
    }
}
