#ifndef RECEIVER_H
#define RECEIVER_H

#include <QLineF>
#include "ReceiverObserver.h"
#include "AbstractScene.h"
#include "GraphicsReceiver.h"
#include "MovableObject.h"
#include <QPointF>
#include "AbstractReceiver.h"
#include "ray.h"
#include <complex>


using namespace  std;

class Receiver:public MovableObject, public QPointF, public AbstractReceiver
{
public:
    enum Mode {RayTracing, Coverege};
    Receiver(QPointF pos, AbstractScene *scene, Mode myMode = RayTracing);
    ~Receiver(void);
    void computeEMField();
    void addAntenaImage(ReceiverObserver *antenaImage);
    void addToScene();
    void moveToPosition(const QPointF &pos) override;
    void notifyObservers();
    void addWholeRay(vector<ray> *wholeRay) override;
    void addRaysToScene();
    void addWholeRayToScene(vector<ray> *wholeRay);
    QPointF getPosition()const override;

private:
    AbstractScene *m_scene;
    GraphicsReceiver* m_graphicsReceiver;
    vector <vector <ray>*> m_wholeRays;
    vector <ReceiverObserver*> m_antenaImages;
    Mode m_mode;
};

#endif // RECEIVER_H
