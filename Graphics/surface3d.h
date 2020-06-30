#ifndef SURFACE3D_H
#define SURFACE3D_H

#include "Product/TransmitterProduct/transmitterproduct.h"

#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QHeightMapSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>
#include <QtWidgets/QSlider>
#include <iostream>

using namespace QtDataVisualization;
using namespace std;

class Surface3D : public QObject
{
    Q_OBJECT
public:
    explicit Surface3D(Q3DSurface *surface, TransmitterProduct *dialog);
    ~Surface3D();

    void enablePatternModel(bool enable);

    void toggleModeNone() { m_graph->setSelectionMode(QAbstract3DGraph::SelectionNone); }
    void toggleModeItem() { m_graph->setSelectionMode(QAbstract3DGraph::SelectionItem); }
    void toggleModeSliceRow() { m_graph->setSelectionMode(QAbstract3DGraph::SelectionItemAndRow
                                                          | QAbstract3DGraph::SelectionSlice); }
    void toggleModeSliceColumn() { m_graph->setSelectionMode(QAbstract3DGraph::SelectionItemAndColumn
                                                             | QAbstract3DGraph::SelectionSlice); }

    void setBlackToYellowGradient();
    void setGreenToRedGradient();

public Q_SLOTS:
    void changeTheme(int theme);

private:
    Q3DSurface *m_graph;
    QSurfaceDataProxy *m_patternProxy;
    QSurface3DSeries *m_patternSeries;
    TransmitterProduct *m_dialog;
    QSurfaceDataArray *m_dataArray;

    float m_stepTheta;
    float m_stepY;
    float m_thetamin,m_thetamax;
    float m_ymin,m_ymax;
    float m_rmin,m_rmax;

    void fillPatternProxy();
};

#endif // SURFACE3D_H
