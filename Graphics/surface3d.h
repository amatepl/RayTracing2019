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

    void setAxisMinSliderTheta(QSlider *slider) { m_axisMinSliderTheta = slider; }
    void setAxisMaxSliderTheta(QSlider *slider) { m_axisMaxSliderTheta = slider; }
    void setAxisMinSliderY(QSlider *slider) { m_axisMinSliderY = slider; }
    void setAxisMaxSliderY(QSlider *slider) { m_axisMaxSliderY = slider; }

    void adjustThetaMin(int min);
    void adjustThetaMax(int max);
    void adjustYMin(int min);
    void adjustYMax(int max);


public Q_SLOTS:
    void changeTheme(int theme);

private:
    Q3DSurface *m_graph;
    QSurfaceDataProxy *m_patternProxy;
    QSurface3DSeries *m_patternSeries;
    DialogTransmitterProduct *m_dialog;
    QSurfaceDataArray *m_dataArray;

    QSlider *m_axisMinSliderTheta;
    QSlider *m_axisMaxSliderTheta;
    QSlider *m_axisMinSliderY;
    QSlider *m_axisMaxSliderY;
    float m_stepTheta;
    float m_stepY;
    float m_rangeMinTheta, m_rangeMinY;
    float m_thetamin,m_thetamax;
    float m_ymin,m_ymax;
    float m_rmin,m_rmax;

    void fillPatternProxy();
    void setAxisThetaRange(float min, float max);
    void setAxisYRange(float min, float max);
    const QSurfaceDataArray *nullArray(int countArray);
};

#endif // SURFACE3D_H
