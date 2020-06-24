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
#include "Abstract_Factory/raytracingalgorithmfactory.h"

#include "Model/model.h"
#include "Model/raytracing.h"
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
    //void attachObserver(WindowObserver *windowobserver) override;
    //void detachObserver(WindowObserver *windowobserver) override;
    //void notify(int mode) override;
    void modelAnswer(vector<MathematicalRayProduct > *sceneproduct) override;
    void modelAnswer(vector<MathematicalProduct*> sceneproduct) override;
    void modelNotify(vector<MathematicalProduct *> sceneproducts) override;
    void modelNotify(vector<MathematicalRayProduct> *sceneproducts) override;

    QWidget* createToolButton(const QString &text,int id);
    void createActions();
    void createMenus();
    void createToolBox();
    void setGraphicsMode(GraphicsMode mode);
    void setActionMode(ActionMode mode);
    void notifyMap();
    void notifyModel();

private:
    QGraphicsView *view;
    GraphicsMap *m_map;

    SceneFactory *m_receiverFactory, *m_transmitterFactory, *m_buildingFactory,
                 *m_treeFactory, *m_carFactory;
    RayTracingAlgorithmFactory*  m_rayTracingAlgorithmFactory;

    GraphicsMode m_graphicsmode;
    ActionMode m_actionmode;
    //vector<WindowObserver*> m_windowobserver;
    //vector<WindowObserver*>::iterator m_windowobserveriterator;
    Model* m_model;
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
