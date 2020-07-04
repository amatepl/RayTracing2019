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
//#include "Abstract_Factory/raytracingalgorithmfactory.h"

#include "Model/model.h"
#include "Model/raytracing.h"
#include "Model/coverage.h"


#include "Observer/AppInterface.h"
#include "graphicsmap.h"
#include "Observer/windowomodelbservable.h"

using namespace std;

class ApplicationWindow :public QMainWindow,public AppInterface, public WindowModelObservable
{
    Q_OBJECT
public:
    ApplicationWindow(QWidget *parent = nullptr);
    ~ApplicationWindow() override;
    void answer(GraphicsProduct* graphic) override;
    void moveMouse(QPointF mouse) override;
    //void attachObserver(WindowObserver *windowobserver) override;
    //void detachObserver(WindowObserver *windowobserver) override;
    //void notify(int mode) override;

    //ModelObservable
    void modelAnswer(vector<MathematicalRayProduct > *sceneproduct) override;
    void modelAnswer(vector<MathematicalProduct*> sceneproduct) override;
    void modelNotify(vector<MathematicalProduct *> sceneproducts) override;
    void modelNotify(vector<MathematicalRayProduct> *sceneproducts) override;
    void modelNotify(vector<vector<MathematicalRayProduct *> *> sceneproducts) override;

    QWidget* createToolButton(const QString &text,int id);
    QWidget* rayTracingWidget();
    QWidget* coverageWidget();

    void createActions();
    void createMenus();
    void createToolBox();
    void createTabWidget();

    void setGraphicsMode(GraphicsMode mode);
    void setActionMode(ActionMode mode);
    void notifyMap();
    void notifyModel();

private:
    QGraphicsView *view;
    GraphicsMap *m_map;

    SceneFactory *m_receiverFactory, *m_transmitterFactory, *m_buildingFactory,
                 *m_treeFactory, *m_carFactory;
    RayTracing*  m_rayTracingAlgorithm;
    Coverage* m_coverageAlgorithm;

    GraphicsMode m_graphicsmode;
    ActionMode m_actionmode;
    //vector<WindowObserver*> m_windowobserver;
    //vector<WindowObserver*>::iterator m_windowobserveriterator;
    Model* m_model;

    QButtonGroup *m_antennagroup;
    QButtonGroup *m_obstaclegroup;

    QButtonGroup *m_raytracinggroup;
    QPushButton *launch_raytracing;
    QPushButton *launch_coverage;


    QToolBox *m_toolbox;
    QToolBar *m_toolbarobject;

    QToolBar *m_toolbarlaunch;
    QTabWidget* m_tabwidget;
    QLineEdit *sceneposx,*sceneposy;

    QAction *deleteaction;
    QAction *propertiesaction;
    QAction *objectminimize;

    QMenu *m_productmenu;
    QMenu *m_windowmenu;

signals:

public slots:
    void antennaGroupClicked(int);
    void obstacleGroupClicked(int);
    void LaunchRayTracing();
    void launchCoverage();
    void deleteProduct();
    void openProduct();
};

#endif // APPLICATIONWINDOW_H
