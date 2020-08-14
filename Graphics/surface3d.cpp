#include "surface3d.h"
#include <QtDataVisualization/qsurfacedataproxy.h>
#include <QtDataVisualization/qvalue3daxis.h>
#include <QtDataVisualization/q3dscene.h>
#include <QtDataVisualization/q3dcamera.h>
#include <QtDataVisualization/qsurface3dseries.h>
#include <QtDataVisualization/q3dtheme.h>
#include <QtCore/qmath.h>

using namespace QtDataVisualization;

const float sampleCountY = 50.0;
const float sampleCountTheta = 180.0;
const float sampleCountPhy = 90.0;
const float sampleThetaMin = 0.0;
const float sampleThetaMax = 360.0;
const float samplePhyMin = 0.0;
const float samplePhyMax = 180.0;

Surface3D::Surface3D(Q3DSurface *surface, TransmitterProduct *dialog)
    : m_graph(surface), m_dialog(dialog), m_thetamin(0.0),m_thetamax(0.0),m_ymin(0.0),m_ymax(0.0),
      m_rmin(0.0),m_rmax(0.0)
{
    QFont font;
    font.setPointSize(80);
    m_graph->setAxisX(new QValue3DAxis);
    m_graph->axisX()->setTitleVisible(true);
    QString x_axe = QChar(0x03C6);
    m_graph->axisX()->setTitle(x_axe);
    m_graph->setAxisY(new QValue3DAxis);
    m_graph->axisY()->setTitleVisible(true);
    m_graph->axisY()->setTitle("Z");
    m_graph->setAxisZ(new QValue3DAxis);
    m_graph->axisZ()->setTitleVisible(true);
    m_graph->axisZ()->setTitle("r");
    m_graph->setPolar(true);
    m_graph->activeTheme()->setType(Q3DTheme::ThemeDigia);
    m_graph->activeTheme()->setFont(font);
    m_graph->activeTheme()->setBackgroundEnabled(false);
    m_patternProxy = new QSurfaceDataProxy();
    m_patternSeries = new QSurface3DSeries(m_patternProxy);
}

Surface3D::~Surface3D(){

}

void Surface3D::enablePatternModel()
{
    fillPatternProxy();
    m_patternSeries->setDrawMode(QSurface3DSeries::DrawSurface);
    m_patternSeries->setFlatShadingEnabled(true);

    m_graph->axisX()->setLabelFormat("%.2f");
    m_graph->axisZ()->setLabelFormat("%.2f");
    m_graph->axisX()->setRange(m_thetamin, m_thetamax);
    m_graph->axisY()->setRange(m_ymin , m_ymax);
    m_graph->axisZ()->setRange(m_rmin, m_rmax + 0.1);
    m_graph->axisX()->setLabelAutoRotation(30);
    m_graph->axisY()->setLabelAutoRotation(90);
    m_graph->axisZ()->setLabelAutoRotation(30);
    m_graph->scene()->activeCamera()->setYRotation(45);
    m_graph->scene()->activeCamera()->setXRotation(225);
    m_graph->scene()->activeCamera()->setZoomLevel(60.0);

    m_graph->addSeries(m_patternSeries);

    m_stepTheta = (sampleThetaMax - sampleThetaMin) / float(sampleCountTheta - 1);
    m_stepY = (m_ymax - m_ymin) / float(sampleCountY - 1);

    QLinearGradient gr;
    gr.setColorAt(0.0, QColor(255,255,0));
    gr.setColorAt(1.0/6.0, QColor(255,153,0));
    gr.setColorAt(2.0/6.0, QColor(255,0,0));
    gr.setColorAt(3.0/6.0, QColor(153,0,153));
    gr.setColorAt(4.0/6.0,QColor(255,0,0));
    gr.setColorAt(5.0/6.0,QColor(255,153,0));
    gr.setColorAt(6.0/6.0,QColor(255,255,0));

    m_graph->seriesList().at(0)->setBaseGradient(gr);
    m_graph->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
}

void Surface3D::fillPatternProxy()
{
    float stepTheta = (sampleThetaMax - sampleThetaMin) / sampleCountTheta;
    float stepPhy = (samplePhyMax - samplePhyMin) / sampleCountPhy;

    if (!m_patternArray)
        m_patternArray = new QSurfaceDataArray;

    m_patternArray = new QSurfaceDataArray;
    m_patternArray->reserve(sampleCountPhy);
    for (int i = 0 ; i < sampleCountPhy; i++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(sampleCountTheta);
        // Keep values within range bounds, since just adding step can cause minor drift due
        // to the rounding errors.
        float phy = qMin(samplePhyMax, (i * stepPhy + samplePhyMin));
        int index = 0;
        for (int j = 0; j < sampleCountTheta; j++) {
            float theta = qMin(sampleThetaMax, (j * stepTheta + sampleThetaMin));
            double gain = abs(m_dialog->totaleArrayFactor(double(theta),double(phy)));
            float xtheta = theta*M_PI/180.0;
            m_thetamax = qMax(xtheta,m_thetamax);
            m_thetamin = qMin(xtheta,m_thetamin);
            float y = gain*qCos(phy*M_PI/180.0);
            m_ymin = qMin(y,m_ymin);
            m_ymax = qMax(y,m_ymax);
            float r = gain;
            m_rmax = qMax(r,m_rmax);
            m_rmin = qMin(r,m_rmin);
            (*newRow)[index++].setPosition(QVector3D(xtheta, y, r));
        }
        *m_patternArray << newRow;
    }
    m_patternProxy->resetArray(m_patternArray);
}
