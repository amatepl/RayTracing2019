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
#include "Abstract_Factory/dialogfactory.h"
#include "Abstract_Factory/receiverfactory.h"
#include "Abstract_Factory/transmitterfactory.h"
#include "Abstract_Factory/buildingfactory.h"
#include "Abstract_Factory/treefactory.h"
#include "Abstract_Factory/carfactory.h"
#include "Abstract_Factory/raytracingalgorithmfactory.h"

#include "Model/model.h"
#include "Model/raytracing.h"

#include "Observer/windowobservable.h"
#include "Observer/windowomodelbservable.h"
#include "graphicscene.h"

#include "Product/CarProduct/graphicscarproduct.h"
#include "Product/TreeProduct/graphicstreeproduct.h"

using namespace std;

class ApplicationWindow :public QMainWindow,public WindowObservable, public WindowModelObservable
{
    Q_OBJECT
public:
    ApplicationWindow(QWidget *parent = nullptr);
    ~ApplicationWindow() override;

    void attachObserver(WindowObserver *windowobserver) override;
    void detachObserver(WindowObserver *windowobserver) override;
    void notify(int mode) override;
    void answer(SceneProduct *sceneproduct) override;
    void modelAnswer(vector<MathematicalRayProduct > *sceneproduct) override;
    void modelAnswer(vector<MathematicalComponent*> sceneproduct) override;
    void modelNotify(vector<SceneProduct *> sceneproducts) override;
    void modelNotify(vector<MathematicalRayProduct *> sceneproducts) override;

    QWidget* createToolButton(const QString &text,int id);
    void createActions();
    void createMenus();
    void createToolBox();

    void setMode(Mode mode);
    void notifyScene();
    void notifyModel();

private:
    QGraphicsView *view;
    SceneFactory *graphicsfactory,*dialogfactory,*mathematicalfactory;
    vector<WindowObserver*> m_windowobserver;
    vector<WindowObserver*>::iterator m_windowobserveriterator;
    GraphicScene *m_scene;
    Model* m_model;

    ReceiverFactory *m_receiverFactory;
    TransmitterFactory *m_transmitterFactory;
    BuildingFactory *m_buildingFactory;
    TreeFactory *m_treeFactory;
    CarFactory *m_carFactory;
    RayTracingAlgorithmFactory* m_rayTracingAlgorithmFactory;


    Mode m_mode;
    vector<SceneProduct*> m_sceneProducts;

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
