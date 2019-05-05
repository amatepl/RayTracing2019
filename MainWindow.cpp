#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IEEE80211g)
{
    ui->setupUi(this);   // basic Qt, arrow -> is the same as (ui*).setupUi()

    scene = new room(this);
    scene_help = new help();
    scene_settings = new settings();
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

    if(scene->DataComputed()){
        int i = 0, j = 0;
        scene->getDataIndices(pos.x(), pos.y(), i, j);
        if(i>0 and j >0){
            ui->Prx->setNum(scene->getPrx(i, j));
            ui->DelaySpread->setNum(scene->getDelay(i, j));
            ui->RiceFactor->setNum(scene->getRiceFactor(i, j));
        }else{
            ui->Prx->setNum(0);
            ui->DelaySpread->setNum(0);
            ui->RiceFactor->setNum(0);
        }
    }
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
    scene_help->show();
}


void MainWindow::on_settingsButton_clicked()
{
    scene_settings->open();
}

void MainWindow::on_plotButton_clicked()
{
   if(scene->DataComputed()){
        scene_plots = new plots();
        int i = 0, j = 0;
        scene->getDataIndices(scene->getTransmitter()->getPosX(), scene->getTransmitter()->getPosY(), i, j);
        scene_plots->plotPathLoss(scene->getData(), i, j, scene->getRows(), scene->getColumns(), scene->getTotalArea());
        scene_plots->show();
   }
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
        scene->drawCoverege();

    }else{
        statusBar()->showMessage("Placing emettor is needed to generate coverage");
    }
}

void MainWindow::on_commandLinkButton_clicked()
{   statusBar()->showMessage("Launch Ray-Tracing");

    if(scene->getReceiver() != NULL || scene->getTransmitter() != NULL){
        ui->spinBoxResult->setValue(scene->distance());

        scene->readSettingsFile();
        scene->launch_algo(true);

        ui->powerResultSpinBox->setValue(scene->getReceivedPower());
        if(scene->getBinaryDebit() > 0){ui->binaryResultsSpinBox->setValue(scene->getBinaryDebit());}


    }else{
        statusBar()->showMessage("Placing the emettor/receptor is requiered");
    }
}

