#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IEEE80211g)

{
    ui->setupUi(this);   // basic Qt, arrow -> is the same as (ui*).setupUi()

    this->setMouseTracking(true);


    //scene = new room(this);
    scene = new room(this);
    //Model model(scene);
    //scene->setSceneRect(0,0,950,500);

    connect(scene,SIGNAL(mouseScenePosition(QPointF&)),this,SLOT(onMouseEvent(QPointF&)));
    connect(scene,SIGNAL(displayResults()),this,SLOT(displayResults()));
    //connect(ui->antena,SIGNAL(on_antena_clicked()),scene,SLOT(setMode(room::MoveItem));
    //scene->installEventFilter(this);


    scene_help = new help();
    scene_settings = new settings();

    scene->setSceneRect(ui->graphicsView->rect());
        ui->graphicsView->setScene(scene);
        ui->graphicsView->ensureVisible(scene->sceneRect());
        cout<<"Scene bottom right x: " <<scene->sceneRect().bottomRight().x()<<endl;
        cout<<"Scene bottom right y: " <<scene->sceneRect().bottomRight().y()<<endl;

        cout<<"Scene top left x: " <<scene->sceneRect().topLeft().x()<<endl;
        cout<<"Scene top left y: " <<scene->sceneRect().topLeft().y()<<endl;

//        ui->spinBoxPosX->setReadOnly(true);
//        ui->spinBoxPosY->setReadOnly(true);
//        ui->spinBoxPosX->setValue(cursor().pos().x());
//        ui->spinBoxPosY->setValue(cursor().pos().y());
//        configureSpinBox(ui->spinBoxPosX, -INT_MIN, +INT_MAX);
//        configureSpinBox(ui->spinBoxPosX, -INT_MIN, +INT_MAX);
        QBrush greenBrush(Qt::green);
        QBrush blueBrush(Qt::blue);
        QPen outlinePen(Qt::black);
        outlinePen.setWidth(2);

        ui->Ptx->setText("Ptx [dBm]: ");
        ui->Prx->setText("Prx [dBm]: ");
        ui->Distance->setText("Distance [m]: ");
        ui->SNR->setText("SNR [dB]: ");
        ui->DelaySpread->setText("Delay spread [ns]: ");
        ui->CoherenceBW->setText("Coherence BW[Hz]: ");
        ui->RiceFactor->setText("Rice Factor [dB]: ");
        ui->coherTime->setText("Coherence time [\u03bcs]: ");
        //setCentralWidget(ui->graphicsView);
        this->centralWidget()->setMouseTracking(true);
        ui->graphicsView->setMouseTracking(true);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::configureSpinBox(QSpinBox *spinBox, int min, int max)const{
    spinBox->setMinimum(min);
    spinBox->setMaximum(max);
}

//bool MainWindow::eventFilter(QObject *target, QEvent *event)
//{
//    if (target == scene)
//    {
//        if (event->type() == QEvent::GraphicsSceneMouseMove)
//        {
//            const QGraphicsSceneMouseEvent* const me = static_cast<const QGraphicsSceneMouseEvent*>(event);
//            const QPointF position = me->scenePos();

//            //scene->mouseMoveEvent(event)

//            onMouseEvent(position);
//        }
//    }
//    return QMainWindow::eventFilter(target, event);
//}



//void MainWindow::mouseMoveEvent(QMouseEvent *event){
//    QWidget::mouseMoveEvent(event);

////    cout<<event->x()<<endl;
////    cout<<event->y()<<endl;

//}


//void MainWindow::mousePressEvent(QMouseEvent *event){
//    //onMouseEvent("lala", event->pos());
//    QWidget::mousePressEvent(event);
//}


//void MainWindow::mouseReleaseEvent(QMouseEvent *event){
//    QWidget::mouseReleaseEvent(event);
//}


//void MainWindow::onMouseEvent(const QString &eventName, const QPoint &pos){
void MainWindow::onMouseEvent(QPointF &pos){
    //QPoint scene->getMousePosition() ;


    QString message = "x = "+ QString::number(pos.x())+", y = "+ QString::number(pos.y());
    statusBar()->showMessage(message);

    if(scene->DataComputed()){
        int i = 0, j = 0;
        scene->getDataIndices(pos.x(), pos.y(), i, j);
        if(!scene->workingZone(pos.x(), pos.y())){
            ui->Ptx->setText(QString("Ptx [dBm]: ") + QString::number(scene->dBm(scene->getpowerEmettor())));
            ui->Prx->setText(QString("Prx [dBm]: ") + QString::number(scene->getPrx(i, j)));
            ui->Distance->setText(QString("Distance [m]: ") + QString::number(scene->getDistance(i, j)));
            ui->SNR->setText(QString("SNR [dB]: ") + QString::number(scene->getSNR(i, j)));
            ui->DelaySpread->setText(QString("Delay spread [ns]: ") + QString::number(scene->getDelay(i, j)*1e+9));
            ui->CoherenceBW->setText(QString("Coherence BW[MHz]: ") + QString::number(1/(scene->getDelay(i, j))*1e-6));
            ui->RiceFactor->setText(QString("Rice Factor [dB]: ") + QString::number(scene->getRiceFactor(i, j)));
            ui->coherTime->setText(QString("Coherence time [s]: ") + QString::number(scene->getCoTime()));
        }else{
            ui->Ptx->setText("Ptx [dBm]: ");
            ui->Prx->setText("Prx [dBm]: ");
            ui->Distance->setText("Distance [m]: ");
            ui->SNR->setText("SNR [dB]: ");
            ui->DelaySpread->setText("Delay spread [ns]: ");
            ui->CoherenceBW->setText("Coherence BW[Hz]: ");
            ui->RiceFactor->setText("Rice Factor [dB]: ");
            ui->coherTime->setText(QString("Coherence time [\u03bcs]: ") + QString::number(scene->getCoTime()));
        }
    }
}


void MainWindow::on_antena_clicked()
{   statusBar()->showMessage("Place the antena");
    scene->setMode(room::InsertItem);
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
    scene->removeAntenas();
    scene->clear();
    scene->drawBuildings();
//    scene->drawWalls();
//    scene = new room;
//    scene->setSceneRect(ui->graphicsView->rect());
//       ui->graphicsView->setScene(scene);
//       ui->graphicsView->ensureVisible(scene->sceneRect());

//       ui->spinBoxPosX->setReadOnly(true);
//       ui->spinBoxPosY->setReadOnly(true);
//       ui->spinBoxPosX->setValue(cursor().pos().x());
//       ui->spinBoxPosY->setValue(cursor().pos().y());
//       ui->spinBoxResult->setValue(0);
//       ui->powerResultSpinBox->setValue(0);
//       ui->binaryResultsSpinBox->setValue(0);
}

void MainWindow::on_generateCoveragePushButton_clicked()
{   statusBar()->showMessage("Launch map coverage");

    if(scene->getTransmitter() != NULL){
        scene->readSettingsFile();
        scene->drawCoverege();
        writePenetrationDepth();

    }else{
        statusBar()->showMessage("Placing emettor is needed to generate coverage");
    }
}

void MainWindow::on_commandLinkButton_clicked()
{   statusBar()->showMessage("Launch Ray-Tracing");
    if(scene->getReceiver() != NULL || scene->getTransmitter() != NULL){
//        ui->spinBoxResult->setValue(scene->distance());

        scene->readSettingsFile();
        scene->launch_algo(true);

//        ui->powerResultSpinBox->setValue(scene->getReceivedPower());
//        if(scene->getBinaryDebit() > 0){ui->binaryResultsSpinBox->setValue(scene->getBinaryDebit());}

        // Display results
        // Watt display
        // ui->Ptx->setText(QString("Ptx [dBm]: ") + QString::number(scene->getpowerEmettor()));
        // ui->Prx->setText(QString("Prx [dBm]: ") + QString::number(scene->dBmRev(scene->getReceivedPower())));

        // dBm display
        displayResults();
    }else{
        statusBar()->showMessage("Placing the emettor/receptor is requiered");
    }
}


void MainWindow::displayResults(){
    ui->Ptx->setText(QString("Ptx [dBm]: ") + QString::number(scene->dBm(scene->getpowerEmettor())));
    ui->Prx->setText(QString("Prx [dBm]: ") + QString::number(scene->getReceivedPower()));

    ui->Distance->setText(QString("Distance [m]: ") + QString::number(scene->distance()));
    ui->SNR->setText(QString("SNR [dB]: ") + QString::number(scene->getSNR_local()));
    ui->DelaySpread->setText(QString("Delay spread [ns]: ") + QString::number(scene->getDelay_local()*1e+9));
    ui->CoherenceBW->setText(QString("Coherence BW[MHz]: ") + QString::number(1/(scene->getDelay_local())*1e-6));
    ui->RiceFactor->setText(QString("Rice Factor [dB]: ") + QString::number(scene->getRiceFactor_local()));
    ui->coherTime->setText(QString("Coherence time [\u03bcs]: ") + QString::number(scene->getCoTime()));
}

void MainWindow::writePenetrationDepth(){
//    map<const char*,int>* st = scene->getStreetsPenDep();
//    ui->commerceUp->setText(QString("Rue du Commerce Up: ") + QString::number((*st)["commerceUp"]));
//    cout<<(*st)["commerceUp"]<<endl;
//    cout<<(*text)["commerceUp"]<<endl;
//    cout<<(*text).size()<<endl;
//    cout<<(*text)["deuxEg"]<<endl;
    float text[5] = {scene->getStPenetrationDepth()[0],scene->getStPenetrationDepth()[1],scene->getStPenetrationDepth()[2],scene->getStPenetrationDepth()[3],scene->getStPenetrationDepth()[4]};
    ui->commerceUp->setText(QString("Rue du Commerce Up [m]: ") + QString::number(text[0]));
    ui->commerceDown->setText(QString("Rue du Commerce Down [m]: ") + QString::number(text[3]));
    ui->deuxEg->setText(QString("Rue de deux Eglises [m]: ") + QString::number(text[1]));
    ui->spa->setText(QString("Rue de spa [m]: ") + QString::number(text[2]));
    ui->indu->setText(QString("Rue de l'Industrie [m]: ") + QString::number(text[4]));

}
