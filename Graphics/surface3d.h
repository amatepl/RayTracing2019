#ifndef SURFACE3D_H
#define SURFACE3D_H

#include "Product/TransmitterProduct/transmitterproduct.h"

#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QHeightMapSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>
#include <QtWidgets/QSlider>
#include <QtCore/QTimer>
#include <iostream>

using namespace QtDataVisualization;
using namespace std;

class Surface3D : public QObject
{
    Q_OBJECT
public:
    explicit Surface3D(Q3DSurface *surface, TransmitterProduct *dialog);
    ~Surface3D();

    void enablePatternModel();

    void toggleModeNone() { m_graph->setSelectionMode(QAbstract3DGraph::SelectionNone); }
    void toggleModeItem() { m_graph->setSelectionMode(QAbstract3DGraph::SelectionItem); }
    void toggleModeSliceRow() { m_graph->setSelectionMode(QAbstract3DGraph::SelectionItemAndRow
                                                          | QAbstract3DGraph::SelectionSlice); }
    void toggleModeSliceColumn() { m_graph->setSelectionMode(QAbstract3DGraph::SelectionItemAndColumn
                                                             | QAbstract3DGraph::SelectionSlice); }


private:
    Q3DSurface *m_graph;
    QTimer m_rotationTimer;
    QSurfaceDataProxy *m_patternProxy;
    QSurface3DSeries *m_patternSeries;
    QSurfaceDataArray *m_patternArray;
    TransmitterProduct *m_dialog;

    float m_stepTheta;
    float m_stepY;
    float m_thetamin,m_thetamax;
    float m_ymin,m_ymax;
    float m_rmin,m_rmax;

    float m_angleOffset;
    float m_angleStep;

    //int m_fieldLines;
    //int m_arrowsPerLine;

    void fillPatternProxy();
};

#endif // SURFACE3D_H
