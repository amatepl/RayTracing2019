#ifndef GRAPHICSTX_H
#define GRAPHICSTX_H
#include <iostream>

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <vector>
#include <QDialog>

#include "txinterface.h"
#include "Product/graphicsproduct.h"
#include "Share/dialogfctry.h"

using namespace std;

class GraphicsTx :public QGraphicsPixmapItem, public GraphicsProduct
{
public:
    GraphicsTx(QMenu* productmenu, QGraphicsScene *scene);
    ~GraphicsTx() override;

    void drawRays(vector<GraphicsProduct*> rays);

    bool graphicsSelected() override;
    void draw() override;

    static QPixmap getImage();

    //int getModel() override;

    //void setModel(Model model) override;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    void notifyToGraphic(QPointF *point, double orientation) override;

    void setDialogFctry(DialogWinFctry<QDialog> *dialogFctry);
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *) override;

private:
    QGraphicsScene *m_scene;
    QMenu* m_productmenu;
    DialogWinFctry<QDialog> *m_dialogFctry;
    unique_ptr<QDialog> m_dialog;
};

#endif // GRAPHICSTX_H
