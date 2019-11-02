#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    newScene = new MapView(this);
    newScene->setSceneRect(QRect(0,0,5000,5000));

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
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
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
