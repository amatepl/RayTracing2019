#ifndef SURFACE3D_H
#define SURFACE3D_H

#include "Product/TransmitterProduct/mathematicaltransmitterproduct.h"
#include "Product/TransmitterProduct/dialogtransmitterproduct.h"

#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QHeightMapSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>
#include <QtWidgets/QSlider>
#include <iostream>

class DialogTransmitterProduct;

using namespace QtDataVisualization;
using namespace std;

class Surface3D : public QObject
{
    Q_OBJECT
public:
    explicit Surface3D(Q3DSurface *surface, DialogTransmitterProduct *dialog);
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

    void setAxisMinSliderX(QSlider *slider) { m_axisMinSliderX = slider; }
    void setAxisMaxSliderX(QSlider *slider) { m_axisMaxSliderX = slider; }
    void setAxisMinSliderZ(QSlider *slider) { m_axisMinSliderZ = slider; }
    void setAxisMaxSliderZ(QSlider *slider) { m_axisMaxSliderZ = slider; }

    void adjustXMin(int min);
    void adjustXMax(int max);
    void adjustZMin(int min);
    void adjustZMax(int max);


public Q_SLOTS:
    void changeTheme(int theme);

private:
    Q3DSurface *m_graph;
    QSurfaceDataProxy *m_patternProxy;
    QSurface3DSeries *m_patternSeries;
    DialogTransmitterProduct *m_dialog;

    QSlider *m_axisMinSliderX;
    QSlider *m_axisMaxSliderX;
    QSlider *m_axisMinSliderZ;
    QSlider *m_axisMaxSliderZ;
    float m_stepX;
    float m_stepZ;
    float m_rangeMinX, m_rangeMinZ;
    float m_xmin,m_xmax;
    float m_ymin,m_ymax;
    float m_zmin,m_zmax;

    void fillPatternProxy();
    void setAxisXRange(float min, float max);
    void setAxisZRange(float min, float max);
};

#endif // SURFACE3D_H
