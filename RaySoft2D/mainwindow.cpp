#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    createActions();
    createMenus();

    newScene = new MapView(itemMenu,this);
    //newScene->setSceneRect(QRect(0,0,3000,3000));

    map = new QGraphicsView(this);
    map->setScene(newScene);

    generateCentralWidget();
    generateToolBar();

    connect(newScene, &MapView::itemInserted,
                this, &MainWindow::itemInserted);
    connect(launch,SIGNAL(clicked()),this,SLOT(launchClicked()));
}

void MainWindow::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = map->matrix();
    map->resetMatrix();
    map->translate(oldMatrix.dx(), oldMatrix.dy());
    map->scale(newScale, newScale);
}


void MainWindow::generateToolBar()
{
    QToolButton *pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/images/mousePointerMove.png"));
    pointerButton->setToolTip("Move Items");

    QToolButton *buttonAntenna = new QToolButton;
    buttonAntenna->setIcon(QIcon(AntennaView::image()));
    buttonAntenna->setCheckable(true);
    buttonAntenna->setToolTip("Put antenna");

    QToolButton *buttonWall = new QToolButton;
    buttonWall->setIcon(QIcon(WallView::image()));
    buttonWall->setCheckable(true);
    buttonWall->setToolTip("Put wall");

    QToolButton *buttonBuilding = new QToolButton;
    buttonBuilding->setIcon(QIcon(BuildingView::image()));
    buttonBuilding->setCheckable(true);
    buttonBuilding->setToolTip("Put building");

    modeButton = new QButtonGroup(this);
    modeButton->addButton(pointerButton,int(MapView::MoveItem));
    modeButton->addButton(buttonAntenna,int(MapView::InsertAntenna));
    modeButton->addButton(buttonWall,int(MapView::InsertWall));
    modeButton->addButton(buttonBuilding,int(MapView::InsertBuilding));

    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("25%") << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::sceneScaleChanged);

    modeToolBar = addToolBar(tr("Mode type"));
    modeToolBar->addWidget(pointerButton);
    modeToolBar->addWidget(buttonAntenna);
    modeToolBar->addWidget(buttonWall);
    modeToolBar->addWidget(buttonBuilding);

    modeToolBar->addWidget(sceneScaleCombo);

    connect(modeButton,QOverload<int>::of(&QButtonGroup::buttonClicked),this,&MainWindow::modeButtonClicked);
    connect(modeButton, QOverload<int>::of(&QButtonGroup::buttonClicked),
            this, &MainWindow::modeButtonChoice);
}

void MainWindow::generateCentralWidget()
{
    powTx = new QLineEdit(this);
    powRx = new QLineEdit(this);
    distance = new QLineEdit(this);
    snr = new QLineEdit(this);
    delaySpread = new QLineEdit(this);
    coherenceBw = new QLineEdit(this);
    riceFactor = new QLineEdit(this);
    coherenceTime = new QLineEdit(this);

    powTx->setReadOnly(true);
    powRx->setReadOnly(true);
    distance->setReadOnly(true);
    snr->setReadOnly(true);
    delaySpread->setReadOnly(true);
    coherenceBw->setReadOnly(true);
    riceFactor->setReadOnly(true);
    coherenceTime->setReadOnly(true);

    channelFormLayout = new QFormLayout(this);
    channelFormLayout->addRow("Ptx [dBm]: ", powTx);
    channelFormLayout->addRow("Prx [dBm]: ", powRx);
    channelFormLayout->addRow("Distance [m]: ", distance);
    channelFormLayout->addRow("SNR [dB]: ",snr);
    channelFormLayout->addRow("Delay spread [ns]: ",delaySpread);
    channelFormLayout->addRow("Coherence bandwidth [Hz]: ",coherenceBw);
    channelFormLayout->addRow("Rice Factor [dB]: ",riceFactor);
    channelFormLayout->addRow("Coherence time [µs]: ",coherenceTime);

    channelProperties = new QGroupBox("Channel properties");
    channelProperties->setLayout(channelFormLayout);

    quit = new QPushButton("Quit",this);
    launch = new QPushButton("Illumination zone",this);
    buttonWindow = new QHBoxLayout(this);
    buttonWindow->setAlignment(Qt::AlignRight);
    buttonWindow->addWidget(quit);
    buttonWindow->addWidget(launch);

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(map,0,0,2,2);
    mainLayout->addWidget(channelProperties,0,2);
    mainLayout->addLayout(buttonWindow,1,2);

    mainWidget = new QWidget(this);
    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);
}

void MainWindow::createActions()
{
    toFrontAction = new QAction(QIcon(":/images/bringToFront.png"),
                                tr("Bring to &Front"), this);
    toFrontAction->setShortcut(tr("Ctrl+F"));
    toFrontAction->setStatusTip(tr("Bring item to front"));
    connect(toFrontAction, &QAction::triggered, this, &MainWindow::bringToFront);

    sendBackAction = new QAction(QIcon(":/images/sendToBack.png"), tr("Send to &Back"), this);
    sendBackAction->setShortcut(tr("Ctrl+T"));
    sendBackAction->setStatusTip(tr("Send item to back"));
    connect(sendBackAction, &QAction::triggered, this, &MainWindow::sendToBack);

    deleteAction = new QAction(QIcon(":/images/delete.png"), tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteItem);

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit Scenediagram example"));
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    lawstreetAction = new QAction(tr("Law street neighborhood"), this);
    connect(lawstreetAction,&QAction::triggered,this,&MainWindow::readLawstreet);

    canyonAction = new QAction(tr("Canyon model"), this);
    connect(canyonAction,&QAction::triggered,this,&MainWindow::readCanyon);
}

void MainWindow::createMenus()
{
    itemMenu = menuBar()->addMenu(tr("&Item"));
    itemMenu->addAction(deleteAction);
    itemMenu->addSeparator();
    itemMenu->addAction(toFrontAction);
    itemMenu->addAction(sendBackAction);

    sceneMenu = menuBar()->addMenu(tr("&Example"));
    sceneMenu->addAction(canyonAction);
    sceneMenu->addAction(lawstreetAction);
}

void MainWindow::deleteItem()
{
    newScene->deleteObject();
}

void MainWindow::bringToFront()
{
    if (newScene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = newScene->selectedItems().first();
    const QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    for (const QGraphicsItem *item : overlapItems) {
        if (item->zValue() >= zValue)
            zValue = item->zValue() + 0.1;
    }
    selectedItem->setZValue(zValue);
}

void MainWindow::sendToBack()
{
    if (newScene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = newScene->selectedItems().first();
    const QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    for (const QGraphicsItem *item : overlapItems) {
        if (item->zValue() <= zValue)
            zValue = item->zValue() - 0.1;
    }
    selectedItem->setZValue(zValue);
}

void MainWindow::itemInserted()
{
    modeButton->button(int(MapView::MoveItem))->setChecked(true);
    newScene->setMode(MapView::Mode(modeButton->checkedId()));
    modeButton->button(int(MapView::InsertAntenna))->setChecked(false);
    modeButton->button(int(MapView::InsertWall))->setChecked(false);
    modeButton->button(int(MapView::InsertBuilding))->setChecked(false);
}

void MainWindow::modeButtonClicked(int id)
{
    const QList<QAbstractButton *> buttons = modeButton->buttons();
    for (QAbstractButton *button : buttons) {
        if (modeButton->button(id) != button)
            button->setChecked(false);
    }
}

void MainWindow::modeButtonChoice(int)
{
    newScene->setMode(MapView::Mode(modeButton->checkedId()));
}

void MainWindow::readLawstreet(){
    newScene->readExamples(":/examples/streetlaw.txt");
}

void MainWindow::readCanyon(){
    newScene->readExamples(":/examples/canyonmodel.txt");
}
