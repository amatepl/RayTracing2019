#ifndef ANTENA_H
#define ANTENA_H
//#include "room.h"
#include <QPointF>
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QBrush>
#include <QPolygonF>
#include <iostream>
#include <QLineF>
#include <AbstractAntena.h>
#include "ReceiverObserver.h"
#include "ray.h"
#include "AbstractReceiver.h"
#include "AbstractScene.h"
#include <complex>

using namespace std;
//class room;
//class QPen;

//class QBrush;

class antena: public QGraphicsEllipseItem,public AbstractAntena, public ReceiverObserver/*, public QPointF*/
{
public:
    antena(/*room *scene = 0,*/ QPointF p = QPointF() , int type = 0);
    ~antena();
    enum Mode {RayTracing, Coverege};
    int getPosX();
    int getPosY();
    QPointF getPos()const;
    void setPosi(QPointF posi);
    QPolygonF getIlluminationZone(const QRectF &rect)const override;

    QPointF sceneRectIntersection(const QRectF &rect, const QLineF &line)const;
    vector <QPointF> boundaryCorners(const QRectF &rect, const QPolygonF &unboundedZone)const;
    void notifyParent(const QPointF &point, vector<ray>* wholeRay) override;
    QPointF getPosition()const override;
    QPolygonF getIlluminationZone()const override;
    void setSceneBoundary(const QRectF &rect);
    void setIlluminatedZone(const QPolygonF &zone) override;
    QPolygonF getIlluminatedZone()const override;
    void notifyObserver(const QPointF &pos) override;
    void setReceiver(AbstractReceiver *receiver);
    void setScene(AbstractScene* scene);
    complex<double>getEMfield()const;
    double getPower()const;
    void setMode(Mode mode);
    vector<vector<ray>*>* getWholeRays();

private:
    //room *myRoom;
    QPointF m_pos;
    int antenaType;
    QPen setColor();
    QPointF m_vector;
    QRectF m_sceneBoundary;
    QPolygonF m_zone;
    AbstractReceiver *m_receiver;
    AbstractScene* m_scene;
    complex<double> m_EMfield;
    vector<vector<ray>*> m_wholeRays;
    double m_power;
    Mode m_mode;

};

#endif // ANTENA_H
