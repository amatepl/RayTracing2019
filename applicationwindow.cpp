#include "applicationwindow.h"

ApplicationWindow::ApplicationWindow(QWidget *parent) : QMainWindow(parent)
{
    createToolBox();
    view = new QGraphicsView();
    graphicsfactory = new GraphicsFactory(view,this);
    dialogfactory = new DialogFactory(dynamic_cast<SceneObservable*>(graphicsfactory));
    dynamic_cast<GraphicsFactory*>(graphicsfactory)->attachObserver(dynamic_cast<SceneObserver*>(dialogfactory));
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
    for(int i = 0;i<antennabuttons.length();i++){
        antennabuttons.at(i)->setChecked(false);
    }
}

QWidget* ApplicationWindow::createToolButton(const QString &text, int mode){
    QWidget *widget = new QWidget;
    QToolButton *button = new QToolButton;
    button->setIconSize(QSize(30, 30));
    button->setCheckable(true);
    QIcon icon;
    switch(mode){
        case int(InsertTransmitter):
            icon = QIcon(GraphicsTransmitterProduct::getImage());
            break;
        case int(InsertReceiver):
            icon = QIcon(GraphicsReceiverProduct::getImage());
            break;
    }
    button->setIcon(icon);
    m_antennagroup->addButton(button,mode);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    widget->setLayout(layout);
    return widget;
}

void ApplicationWindow::createToolBox(){
    m_antennagroup = new QButtonGroup(this);
    m_antennagroup->setExclusive(false);
    connect(m_antennagroup,SIGNAL(buttonClicked(int)),this,SLOT(antennaGroupClicked(int)));
    QGridLayout *layout = new QGridLayout;

    QWidget* widget = createToolButton("Insert Transmitter",int(GraphicsFactory::InsertTransmitter));
    layout->addWidget(widget, 0, 0);
    QWidget* widget1 = createToolButton("Insert Receiver",int(GraphicsFactory::InsertReceiver));
    layout->addWidget(widget1, 0, 1);

    layout->setRowStretch(3, 10);
    layout->setColumnStretch(2, 10);

    QWidget *itemWidget = new QWidget;
    itemWidget->setLayout(layout);

    m_toolbox = new QToolBox;
    m_toolbox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    m_toolbox->setMinimumWidth(itemWidget->sizeHint().width());
    m_toolbox->addItem(itemWidget, tr("Antenna"));
}

void ApplicationWindow::setMode(Mode mode){
    m_mode = mode;
}

void ApplicationWindow::antennaGroupClicked(int mode){
    setMode(Mode(mode));
    notify(mode);
}
