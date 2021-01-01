#include "applicationwindow.h"
#include "Share/wholeray.h"
#include "Share/params.h"

float px_to_meter = 0.5;  // meter per pixel

ApplicationWindow::ApplicationWindow(QWidget *parent) : QMainWindow(parent, Qt::WindowStaysOnBottomHint)
{
//    setWindowFlag(Qt::WindowStaysOnBottomHint);
    createToolBox();
    createToolInfo();
    createActions();
    createMenus();
    view = new QGraphicsView();
    view->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    m_map = new GraphicsMap(view, this, m_productmenu);
    m_map->installEventFilter(this);
    connect(m_map, &GraphicsMap::eField, m_info_widget, &InfoWidget::updateEField);
    view->setMouseTracking(true);
    m_receiverFactory = new ReceiverFactory(m_productmenu, m_info_widget, m_map, px_to_meter, this);
    m_transmitterFactory = new TransmitterFactory(m_productmenu, m_map, px_to_meter);
    m_buildingFactory = new BuildingFactory(m_productmenu, m_map, px_to_meter);
    m_treeFactory = new TreeFactory(m_productmenu, m_map, px_to_meter);
    m_carFactory = new CarFactory(m_productmenu, m_map, px_to_meter);

    m_model = new Model(this);
    m_model->setScene(m_map, (BuildingFactory *) m_buildingFactory,
                      (TreeFactory *) m_treeFactory,
                      (CarFactory *) m_carFactory,
                      (ReceiverFactory *) m_receiverFactory);
    m_info_widget->sendGenerateMap();

    m_rayTracingAlgorithm = new RayTracing(px_to_meter);
    m_rayTracingAlgorithm->setScene(m_map);

    m_coverageAlgorithm = new Coverage(m_receiverFactory, px_to_meter);
    m_coverageAlgorithm->setScene(m_map);
    connect(m_coverageAlgorithm, &Coverage::computed, this, &ApplicationWindow::addHeatMap);

    addToolBar(Qt::LeftToolBarArea, m_toolbarobject);
    addToolBar(Qt::TopToolBarArea, m_toolinfo);
    setCentralWidget(view);
    setWindowState(Qt::WindowMaximized);

    m_graphicsmode = MoveItem;
}

ApplicationWindow::~ApplicationWindow()
{

}

void ApplicationWindow::answer(GraphicsProduct* graphic)
{
    m_graphicsmode = MoveItem;
    QList<QAbstractButton*> antennabuttons = m_antennagroup->buttons();
    QList<QAbstractButton*> obstaclebuttons = m_obstaclegroup->buttons();
    for(QAbstractButton *button: antennabuttons) {
        button->setChecked(false);
    }
    for(QAbstractButton *button: obstaclebuttons) {
        button->setChecked(false);
    }
    m_model->addMathematicalComponent(graphic->toMathematicalProduct());
}

void ApplicationWindow::deleteAnswer(GraphicsProduct *graphic){
    m_model->removeMathematicalComponent(graphic->toMathematicalProduct());
}

void ApplicationWindow::moveMouse(QPointF mouse){
    m_info_widget->changeScenePos(mouse.x(),mouse.y());
}

void ApplicationWindow::resetToolInfo(){
    m_info_widget->reset();
}

/*
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
*/

//    notify(int(m_mode));

void ApplicationWindow::modelAnswer(vector<MathematicalProduct *> sceneproducts)
{
    for(unsigned i = 0; i< sceneproducts.size(); i++) {
        m_map->addItem((QGraphicsItem*)sceneproducts.at(i)->toGraphicsProduct());
    }
}

void ApplicationWindow::modelAnswer(vector<Ray> *sceneproducts)
{
    for(unsigned i = 0; i< sceneproducts->size(); i++) {

        QGraphicsItem* gItem = dynamic_cast<QGraphicsItem*>(sceneproducts->at(i).toGraphicsProduct());

        m_map->addItem(gItem);
    }
}

void ApplicationWindow::modelNotify(vector<MathematicalProduct *> sceneproducts)
{
    for(unsigned i = 0; i< sceneproducts.size(); i++) {

        QGraphicsItem* gItem = dynamic_cast<QGraphicsItem*>(sceneproducts.at(i)->toGraphicsProduct());
        m_map->addItem(gItem);
    }
}

void ApplicationWindow::modelNotify(vector<Ray > *sceneproducts)
{
    for(unsigned i = 0; i< sceneproducts->size(); i++) {

        QGraphicsItem* gItem = dynamic_cast<QGraphicsItem*>(sceneproducts->at(i).toGraphicsProduct());
        m_map->addItem(gItem);
    }
}

void ApplicationWindow::modelNotify(vector<WholeRay *> sceneproducts)
{
    for(unsigned i = 0; i< sceneproducts.size(); i++) {
        for(unsigned j = 0; j<sceneproducts.at(i)->size(); j++) {

            QGraphicsItem* gItem = dynamic_cast<QGraphicsItem*>(sceneproducts.at(i)->at(
                                       j)->toGraphicsProduct());

            m_map->addItem(gItem);

        }
    }
}

QWidget* ApplicationWindow::createToolButton(const QString &text, int mode)
{
    QWidget *widget = new QWidget;
    QToolButton *button = new QToolButton;
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);
    QIcon icon;
    switch(mode) {
    case int(InsertTransmitter):
        icon = QIcon(GraphicsTx::getImage());
        button->setIcon(icon);
        m_antennagroup->addButton(button,mode);
        break;
    case int(InsertReceiver):
        icon = QIcon(GraphicsRx::getImage());
        button->setIcon(icon);
        m_antennagroup->addButton(button,mode);
        break;
    case int(InsertBuilding):
        icon = QIcon(GraphicsBuilding::getImage());
        button->setIcon(icon);
        m_obstaclegroup->addButton(button,mode);
        break;
//    case int(InsertTree):
//        icon = QIcon(GraphicsTreeProduct::getImage());
//        button->setIcon(icon);
//        m_obstaclegroup->addButton(button,mode);
//        break;
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

    objectminimize = m_toolbarobject->toggleViewAction();
    objectminimize->setText(tr("Object toolbar"));
    deleteaction = new QAction(QIcon(":/Images/Delete.png"), tr("&Delete"), this);
    deleteaction->setShortcut(tr("Delete"));
    deleteaction->setStatusTip(tr("Delete selected object"));

    propertiesaction = new QAction(QIcon(":/Images/Properties.png"), tr("&Properties"), this);
    propertiesaction->setShortcut(tr("Open"));

    connect(deleteaction, &QAction::triggered, this, &ApplicationWindow::deleteProduct);
    connect(propertiesaction, &QAction::triggered, this, &ApplicationWindow::openProduct);

}

void ApplicationWindow::createMenus()
{
    m_windowmenu = menuBar()->addMenu(tr("&Window"));
    m_windowmenu->addAction(objectminimize);

    m_productmenu = menuBar()->addMenu(tr("&Object"));
    m_productmenu->addAction(propertiesaction);
    m_productmenu->addSeparator();
    m_productmenu->addAction(deleteaction);
}

void ApplicationWindow::createToolBox()
{
    /*
     * Creation of ths sidepannel butons
    */
    m_antennagroup = new QButtonGroup(this);
    m_antennagroup->setExclusive(false);
    m_obstaclegroup = new QButtonGroup(this);
    m_obstaclegroup->setExclusive(false);
    connect(m_antennagroup,SIGNAL(buttonClicked(int)),this,SLOT(antennaGroupClicked(int)));
    connect(m_obstaclegroup,SIGNAL(buttonClicked(int)),this,SLOT(obstacleGroupClicked(int)));
    QGridLayout *antenna_layout = new QGridLayout;

    // Creating the antennas pannel
    QWidget* widget = createToolButton("Transmitter",int(InsertTransmitter));
    antenna_layout->addWidget(widget, 0, 0, Qt::AlignTop);
    QWidget* widget1 = createToolButton("Receiver", int(InsertReceiver));
    antenna_layout->addWidget(widget1, 1, 0, Qt::AlignTop);

    QWidget* obstacle_widget = createToolButton("Building",int(InsertBuilding));
    antenna_layout->addWidget(obstacle_widget, 2, 0, Qt::AlignTop);
//    QWidget* tree_widget = createToolButton("Tree", int(InsertTree));
//    antenna_layout->addWidget(tree_widget, 3, 0, Qt::AlignTop);
    QWidget* car_layout = createToolButton("Car", int(InsertCar));
    antenna_layout->addWidget(car_layout, 3, 0, Qt::AlignTop);

    antenna_layout->setRowStretch(4,10);
    antenna_layout->setColumnStretch(1, 10);

    QWidget *itemWidget = new QWidget;
    itemWidget->setLayout(antenna_layout);

    m_toolbox = new QToolBox;
    m_toolbox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    m_toolbox->setMinimumWidth(itemWidget->sizeHint().width());
    m_toolbox->addItem(itemWidget, tr("Insert antenna"));
    m_toolbarobject = new QToolBar;
    m_toolbarobject->addWidget(m_toolbox);
    m_toolbarobject->setFloatable(false);
    m_toolbarobject->setMovable(false);
}

void ApplicationWindow::createToolInfo()
{
    m_toolinfo = new QToolBar;
    m_info_widget = new InfoWidget(m_toolinfo);
    m_toolinfo->addWidget(m_info_widget);

    connect(m_info_widget, &InfoWidget::rayTracing, this, &ApplicationWindow::LaunchRayTracing);
    connect(m_info_widget, &InfoWidget::clearRayTracing, this, &ApplicationWindow::clearRayTracing);
    connect(m_info_widget, &InfoWidget::coverage, this, &ApplicationWindow::launchCoverage);
    connect(m_info_widget, &InfoWidget::clearCoverage, this, &ApplicationWindow::clearCoverage);
    connect(m_info_widget, &InfoWidget::startCars, this, &ApplicationWindow::startCars);
    connect(m_info_widget, &InfoWidget::clear, this, &ApplicationWindow::clearWorkspace);
    connect(m_info_widget, &InfoWidget::generateMap, this, &ApplicationWindow::generateMap);
//    connect(m_info_widget, &InfoWidget::generateMap, m_model, &Model::generateMap);

}

void ApplicationWindow::setGraphicsMode(GraphicsMode mode)
{
    m_graphicsmode = mode;
}

void ApplicationWindow::setActionMode(ActionMode mode)
{
    m_actionmode = mode;
}

void ApplicationWindow::notifyMap()
{
    SceneFactory * factory;
    if (m_graphicsmode != MoveItem) {
        switch (m_graphicsmode) {
        case int(InsertReceiver):
            factory = m_receiverFactory;
            m_map->setSceneFactory(factory);
            break;
        case int(InsertTransmitter):
            factory = m_transmitterFactory;
            m_map->setSceneFactory(factory);
            break;
        case int(InsertBuilding):
            factory = m_buildingFactory;
            m_map->setSceneFactory(factory);
            break;
//        case int(InsertTree):
//            factory = m_treeFactory;
//            m_map->setSceneFactory(factory);
//            break;
        case int(InsertCar):
            factory = m_carFactory;
            m_map->setSceneFactory(factory);
            break;
        default:
            break;
        }
    }
}

void ApplicationWindow::notifyModel()
{
    m_model->launchAlgorithm(m_coverageAlgorithm);
}

bool ApplicationWindow::eventFilter(QObject*, QEvent *event){
    if (event->type() == QEvent::Leave)
    {
        m_info_widget->changeScenePos(0,0);
    }
    return false;
}

// SLOTS

void ApplicationWindow::antennaGroupClicked(int mode)
{
    QList <QAbstractButton*> buttons = m_antennagroup->buttons();
    for (int i = 0; i < buttons.size(); i++) {
        if (buttons.at(i) != m_antennagroup->checkedButton()) {
            buttons.at(i)->setChecked(false);
        }
    }
    if (m_obstaclegroup->checkedButton() != 0) {
        m_obstaclegroup->checkedButton()->setChecked(false);
    }
    setGraphicsMode(GraphicsMode(mode));
    notifyMap();
}

void ApplicationWindow::obstacleGroupClicked(int mode)
{
    QList <QAbstractButton*> buttons = m_obstaclegroup->buttons();
    for (int i = 0; i < buttons.size(); i++) {
        if (buttons.at(i) != m_obstaclegroup->checkedButton()) {
            buttons.at(i)->setChecked(false);
        }
    }
    if (m_antennagroup->checkedButton() != 0) {
        m_antennagroup->checkedButton()->setChecked(false);
    }
    setGraphicsMode(GraphicsMode(mode));
    notifyMap();
}

void ApplicationWindow::LaunchRayTracing(unsigned reflectionsNbr)
{
    m_rayTracingAlgorithm->setReflectionsNbr(reflectionsNbr);
    m_model->launchAlgorithm(m_rayTracingAlgorithm);
}

void ApplicationWindow::clearRayTracing()
{
    m_rayTracingAlgorithm->clear();
}

void ApplicationWindow::launchCoverage(unsigned reflectionsNbr, double dnsty, int type_cov)
{
    m_coverageAlgorithm->setReflectionsNbr(reflectionsNbr);
    m_coverageAlgorithm->setDnsty(dnsty);
    m_coverageAlgorithm->setHeatmapMode(type_cov);
    m_model->launchAlgorithm(m_coverageAlgorithm);
}

void ApplicationWindow::clearCoverage()
{
    m_coverageAlgorithm->clear();
    m_map->clearHeatMap();
}

void ApplicationWindow::startCars()
{
    m_model->startCars();
}

void ApplicationWindow::deleteProduct()
{
    m_map->deleteItem();
}

void ApplicationWindow::openProduct()
{

}

void ApplicationWindow::clearWorkspace()
{
//    m_model->clearWorkspace();
//    m_rayTracingAlgorithm->clearWorkspace();
    m_rayTracingAlgorithm->clear();
    m_coverageAlgorithm->clear();
    m_map->clear();
    m_model->clear();
}

void ApplicationWindow::generateMap(unsigned h, unsigned w, unsigned carDnsty, unsigned strWidth, unsigned strGap)
{
    m_map->setSceneRect(0, 0, w / px_to_meter, h / px_to_meter);
    m_model->generateMap(h, w, carDnsty, strWidth, strGap, px_to_meter);
}

void ApplicationWindow::addHeatMap(HeatMap *heatMap, HeatmapMode mode)
{
    switch (mode) {
    case HeatmapMode::complexE:
        m_map->addHeatMap(heatMap);
        break;
    case HeatmapMode::sumAbsE:
        m_map->addHeatMap(heatMap);
        break;
    case HeatmapMode::prx:
        m_map->addHeatMap(heatMap, GraphicsHeatMap::Mode::prx);
        break;
    default:
        break;
    }

}
