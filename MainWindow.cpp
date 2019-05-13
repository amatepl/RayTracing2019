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

       ui->Prx->setText("Prx [dBm]: 0");
       ui->Distance->setText("Distance [m]: 0");
       ui->DelaySpread->setText("Delay spread [s]: 0");
       ui->RiceFactor->setText("Rice Factor [dB]: 0");
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
        if(i>0 and j>0 and pos.x()<950 and pos.y()<500){
            ui->Prx->setText(QString("Prx [dBm]: ") + QString::number(scene->getPrx(i, j)));
            ui->Distance->setText(QString("Distance [m]: ") + QString::number(scene->getDistance(i, j)));
            ui->DelaySpread->setText(QString("Delay spread [s]: ") + QString::number(scene->getDelay(i, j)));
            ui->RiceFactor->setText(QString("Rice Factor [dB]: ") + QString::number(scene->getRiceFactor(i, j)));
        }else{
            ui->Prx->setText("Prx [dBm]: 0");
            ui->Distance->setText("Distance [m]: 0");
            ui->DelaySpread->setText("Delay spread [s]: 0");
            ui->RiceFactor->setText("Rice Factor [dB]: 0");
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
  if(scene->DataComputed() or scene->getRayNumber()>0){
        scene_plots = new plots();
        int i = 0, j = 0;
        scene->getDataIndices(scene->getTransmitter()->getPosX(), scene->getTransmitter()->getPosY(), i, j);
        scene_plots->plotPathLoss(scene);
        scene_plots->show();
  }
}

void MainWindow::on_clearWorkspaceButton_clicked(){

    scene->clearAll();
    scene->clearPenDepth();
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

void MainWindow::writePenetrationDepth(double text[5]){
//    map<const char*,int>* st = scene->getStreetsPenDep();
//    ui->commerceUp->setText(QString("Rue du Commerce Up: ") + QString::number((*st)["commerceUp"]));
//    cout<<(*st)["commerceUp"]<<endl;
//    cout<<(*text)["commerceUp"]<<endl;
//    cout<<(*text).size()<<endl;
//    cout<<(*text)["deuxEg"]<<endl;
    ui->commerceUp->setText(QString("Rue du Commerce Up: ") + QString::number(text[0]));
    ui->commerceDown->setText(QString("Rue du Commerce Down: ") + QString::number(text[3]));
    ui->deuxEg->setText(QString("Rue de deux Eglises: ") + QString::number(text[1]));
    ui->spa->setText(QString("Rue de spa: ") + QString::number(text[2]));
    ui->indu->setText(QString("Rue de l'Industrie: ") + QString::number(text[4]));
}

