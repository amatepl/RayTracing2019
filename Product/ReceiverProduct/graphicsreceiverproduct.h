#ifndef GRAPHICSRECEIVERPRODUCT_H
#define GRAPHICSRECEIVERPRODUCT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QPainter>

//#include "receiverproduct.h"
#include "Composite/graphicscomponent.h"
#include "Composite/MathematicalComponent.h"

// TEST---
//#include "Product/ReceiverProduct/dialogreceiverproduct.h"
//--------

//class GraphicsFactory;
//class MathematicalComponent;

class GraphicsReceiverProduct :public QGraphicsPixmapItem/*, public ReceiverProduct*/,public GraphicsComponent
{
public:
//    GraphicsReceiverProduct(int posX, int posY, unsigned long frequency, bool enable,QMenu *menuproduct
//                               ,GraphicsFactory* graphicsfactory);
    GraphicsReceiverProduct(int posX, int posY, bool enable, QMenu *menuproduct
                               , QGraphicsScene *scene);
    ~GraphicsReceiverProduct() override;

    void enableReceiver(bool enable);
    QColor scaleColor(double min, double max, double value);
    static QPixmap getImage();

    int getType() override;
    bool graphicsSelected() override;
    void draw() override;

    int getPosX() override;
    int getPosY() override;

    void setPosX(int posX) override;
    void setPosY(int posY) override;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    void setMathematicalComponent(MathematicalComponent *mathematicalComponent) override;

    MathematicalComponent* toMathematicalComponent() override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QRgb m_color;
    int m_posx,m_posy,m_sizex,m_sizey;
    double m_power, m_efield;
    unsigned long m_frequency;
    QGraphicsScene *m_scene;
    MathematicalComponent *m_mathematicalComponent;

    QMenu *m_productmenu;
};

#endif // GRAPHICSRECEIVERPRODUCT_H
