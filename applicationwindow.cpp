#include "applicationwindow.h"

ApplicationWindow::ApplicationWindow(QWidget *parent) : QMainWindow(parent)
{
    createToolBox();
    createActions();
    createMenus();
    view = new QGraphicsView();
    graphicsfactory = new GraphicsFactory(view,this,m_productmenu);
    dialogfactory = new DialogFactory(dynamic_cast<SceneObservable*>(graphicsfactory));
    mathematicalfactory = new MathematicalFactory(dynamic_cast<SceneObservable*>(graphicsfactory));
    dynamic_cast<GraphicsFactory*>(graphicsfactory)->attachObserver(dynamic_cast<SceneObserver*>(dialogfactory));
    dynamic_cast<GraphicsFactory*>(graphicsfactory)->attachObserver(dynamic_cast<SceneObserver*>(mathematicalfactory));

    attachObserver(dynamic_cast<WindowObserver*>(graphicsfactory));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(m_toolbox);
    layout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);

    m_mode = MoveItem;
}

ApplicationWindow::~ApplicationWindow(){

}

void ApplicationWindow::attachObserver(WindowObserver *windowobserver){
    m_windowobserver.push_back(windowobserver);
}

void ApplicationWindow::detachObserver(WindowObserver *windowobserver){
    unsigned long long i = 0;
    for (m_windowobserveriterator = m_windowobserver.begin();
         m_windowobserveriterator != m_windowobserver.end();
         ++m_windowobserveriterator){
        if (m_windowobserver.at(i) == windowobserver){
            m_windowobserver.erase(m_windowobserveriterator);
        }
        i++;
    }
}

void ApplicationWindow::notify(int mode){
    for (unsigned long long i=0;i<m_windowobserver.size();i++){
        m_windowobserver.at(i)->update(mode);
    }
}

void ApplicationWindow::answer(){
    m_mode = MoveItem;
    notify(int(m_mode));
    QList<QAbstractButton*> antennabuttons = m_antennagroup->buttons();
    QList<QAbstractButton*> obstaclebuttons = m_obstaclegroup->buttons();
    for(QAbstractButton *button: antennabuttons){
        button->setChecked(false);
    }
    for(QAbstractButton *button: obstaclebuttons){
        button->setChecked(false);
    }

}

QWidget* ApplicationWindow::createToolButton(const QString &text, int mode){
    QWidget *widget = new QWidget;
    QToolButton *button = new QToolButton;
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);
    QIcon icon;
    switch(mode){
        case int(InsertTransmitter):
            icon = QIcon(GraphicsTransmitterProduct::getImage());
            button->setIcon(icon);
            m_antennagroup->addButton(button,mode);
            break;
        case int(InsertReceiver):
            icon = QIcon(GraphicsReceiverProduct::getImage());
            button->setIcon(icon);
            m_antennagroup->addButton(button,mode);
            break;
        case int(InsertBuilding):
            icon = QIcon(GraphicsBuildingProduct::getImage());
            button->setIcon(icon);
            m_obstaclegroup->addButton(button,mode);
            break;
        case int(InsertTree):
            icon = QIcon(GraphicsTreeProduct::getImage());
            button->setIcon(icon);
            m_obstaclegroup->addButton(button,mode);
        break;
        case int(InsertCar):
            icon = QIcon(GraphicsCarProduct::getImage());
            button->setIcon(icon);
            m_obstaclegroup->addButton(button,mode);
        break;

    }
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    widget->setLayout(layout);
    return widget;
}

void ApplicationWindow::createActions(){
    deleteaction = new QAction(QIcon(":/Images/Delete.png"), tr("&Delete"), this);
    deleteaction->setShortcut(tr("Delete"));
    deleteaction->setStatusTip(tr("Delete selected object"));

    propertiesaction = new QAction(QIcon(":/Images/Properties.png"), tr("&Properties"), this);
    propertiesaction->setShortcut(tr("Open"));

    connect(deleteaction, SIGNAL(triggered()), this, SLOT(deleteProduct()));
    connect(propertiesaction, SIGNAL(triggered()), this, SLOT(openProduct()));

}

void ApplicationWindow::createMenus(){
    m_productmenu = menuBar()->addMenu(tr("&Object"));
    m_productmenu->addAction(propertiesaction);
    m_productmenu->addSeparator();
    m_productmenu->addAction(deleteaction);
}

void ApplicationWindow::createToolBox(){
    /*
     * Creation of ths sidepannel butons
    */
    m_antennagroup = new QButtonGroup(this);
    m_antennagroup->setExclusive(false);
    m_obstaclegroup = new QButtonGroup(this);
    m_obstaclegroup->setExclusive(false);
    m_raytracinggroup = new QButtonGroup(this);
    m_raytracinggroup->setExclusive(false);
    connect(m_antennagroup,SIGNAL(buttonClicked(int)),this,SLOT(antennaGroupClicked(int)));
    connect(m_obstaclegroup,SIGNAL(buttonClicked(int)),this,SLOT(obstacleGroupClicked(int)));
    connect(m_raytracinggroup,SIGNAL(buttonClicked(int)),this,SLOT(rayTracingGroupClicked(int)));
    QGridLayout *antenna_layout = new QGridLayout;
    QGridLayout *obstacle_layout = new QGridLayout;
    QGridLayout *rayTracing_layout = new QGridLayout;

    // Creating the antennas pannel
    QWidget* widget = createToolButton("Transmitter",int(GraphicsFactory::InsertTransmitter));
    antenna_layout->addWidget(widget, 0, 0);
    QWidget* widget1 = createToolButton("Receiver", int(GraphicsFactory::InsertReceiver));
    antenna_layout->addWidget(widget1, 0, 1);

    antenna_layout->setRowStretch(1,10);
    antenna_layout->setColumnStretch(2, 10);

    // Creating the obstacle pannel
    obstacle_layout->setHorizontalSpacing(10);

    QWidget* obstacle_widget = createToolButton("Building",int(GraphicsFactory::InsertBuilding));
    obstacle_layout->addWidget(obstacle_widget, 0, 0);
    QWidget* tree_widget = createToolButton("Tree", int(GraphicsFactory::InsertTree));
    obstacle_layout->addWidget(tree_widget,0,1);
    QWidget* car_layout = createToolButton("Car", int(GraphicsFactory::InsertCar));
    obstacle_layout->addWidget(car_layout,1,0);

    obstacle_layout->setRowStretch(3, 10);
    obstacle_layout->setColumnStretch(2, 10);
    obstacle_layout->setHorizontalSpacing(10);
    QWidget *itemWidget = new QWidget;
    itemWidget->setLayout(antenna_layout);

    QWidget *obstacleWidget = new QWidget;
    obstacleWidget->setLayout(obstacle_layout);

    // Creating the rayTraycing pannel

    QWidget *rayTracingWidget = new QWidget;
    QToolButton *launchRayTracingButton = new QToolButton;
    launchRayTracingButton->setIconSize(QSize(50, 50));
    launchRayTracingButton->setCheckable(false);
    QPixmap iconPixmap(":/Images/playBsmall.png");
    QSize iconNewSize(50,50);
    iconPixmap.scaled(iconNewSize);
    QIcon icon  = QIcon(iconPixmap);
    launchRayTracingButton->setIcon(icon);

    rayTracing_layout->setRowStretch(1,10);
    rayTracing_layout->setColumnStretch(2, 10);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(launchRayTracingButton, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel("Launch Ray Tracing"), 1, 0, Qt::AlignCenter);

    rayTracingWidget->setLayout(layout);

    m_toolbox = new QToolBox;
    m_toolbox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    m_toolbox->setMinimumWidth(itemWidget->sizeHint().width());
    m_toolbox->addItem(itemWidget, tr("Insert antenna"));
    m_toolbox->addItem(obstacleWidget, tr("Insert obstacles"));
    m_toolbox->addItem(rayTracingWidget, tr("Ray Tracing"));
}

void ApplicationWindow::setMode(Mode mode){
    m_mode = mode;
}

// SLOTS

void ApplicationWindow::antennaGroupClicked(int mode){
    QList <QAbstractButton*> buttons = m_antennagroup->buttons();
    for (int i = 0; i < buttons.size(); i++){
        if (buttons.at(i) != m_antennagroup->checkedButton()){
            buttons.at(i)->setChecked(false);
        }
    }
    if (m_obstaclegroup->checkedButton() != 0)
        m_obstaclegroup->checkedButton()->setChecked(false);
    setMode(Mode(mode));
    notify(mode);
}

void ApplicationWindow::obstacleGroupClicked(int mode){
    QList <QAbstractButton*> buttons = m_obstaclegroup->buttons();
    for (int i = 0; i < buttons.size(); i++){
        if (buttons.at(i) != m_obstaclegroup->checkedButton()){
            buttons.at(i)->setChecked(false);
        }
    }
    if (m_antennagroup->checkedButton() != 0)
        m_antennagroup->checkedButton()->setChecked(false);
    setMode(Mode(mode));
    notify(mode);
}

void ApplicationWindow::rayTracingGroupClicked(int mode){
    QList <QAbstractButton*> buttons = m_raytracinggroup->buttons();
    for (int i = 0; i < buttons.size(); i++){
        if (buttons.at(i) != m_raytracinggroup->checkedButton()){
            buttons.at(i)->setChecked(false);
        }
    }
    setMode(Mode(mode));
    notify(mode);
}

void ApplicationWindow::deleteProduct(){
    notify(int(DeleteItem));
}

void ApplicationWindow::openProduct(){
    notify((int(PropertiesItem)));
}
