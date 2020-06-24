#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H
#include <vector>

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QButtonGroup>
#include <QGridLayout>
#include <QToolButton>
#include <QLabel>
#include <QToolBox>
#include <QAction>
#include <QMenu>
#include <QMenuBar>

#include "Abstract_Factory/scenefactory.h"
#include "Abstract_Factory/receiverfactory.h"
#include "Abstract_Factory/transmitterfactory.h"
#include "Abstract_Factory/buildingfactory.h"
#include "Abstract_Factory/treefactory.h"
#include "Abstract_Factory/carfactory.h"

#include "Observer/AppInterface.h"
#include "graphicsmap.h"

using namespace std;

class ApplicationWindow :public QMainWindow,public AppInterface
{
    Q_OBJECT
public:
    ApplicationWindow(QWidget *parent = nullptr);
    ~ApplicationWindow() override;

    void answer() override;

    QWidget* createToolButton(const QString &text,int id);
    void createActions();
    void createMenus();
    void createToolBox();

    void setGraphicsMode(GraphicsMode mode);
    void setActionMode(ActionMode mode);
    void notifyMap();

private:
    QGraphicsView *view;
    GraphicsMap *m_map;

    SceneFactory *m_receiverFactory, *m_transmitterFactory, *m_buildingFactory,
                 *m_treeFactory, *m_carFactory;

    GraphicsMode m_graphicsmode;
    ActionMode m_actionmode;

    QButtonGroup *m_antennagroup;
    QButtonGroup *m_obstaclegroup;
    QButtonGroup *m_raytracinggroup;
    QToolBox *m_toolbox;

    QAction *deleteaction;
    QAction *propertiesaction;

    QMenu *m_productmenu;


signals:

public slots:
    void antennaGroupClicked(int);
    void obstacleGroupClicked(int);
    void rayTracingGroupClicked(int);
    void deleteProduct();
    void openProduct();
};

#endif // APPLICATIONWINDOW_H
