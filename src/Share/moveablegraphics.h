#ifndef MOVEABLEGRAPHICS_H
#define MOVEABLEGRAPHICS_H

#include <QObject>

class MoveableGraphics : public QObject
{
    Q_OBJECT
public:
    virtual ~MoveableGraphics() {}

public slots:
    virtual void notifyToGraphicSig(QPolygonF *, int, int, double) = 0;
};


#endif // MOVEABLEGRAPHICS_H
