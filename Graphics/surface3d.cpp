#include "surface3d.h"

#include <QtDataVisualization/QValue3DAxis>
#include <QtDataVisualization/Q3DTheme>
#include <QtGui/QImage>
#include <QtCore/qmath.h>

using namespace QtDataVisualization;

const int sampleCountX = 50;
const int sampleCountZ = 50;
const int sampleCountTheta = 180;
const int sampleCountPhy = 90;
const float sampleThetaMin = 0.0;
const float sampleThetaMax = 360.0;
const float samplePhyMin = 0.0;
const float samplePhyMax = 180.0;

Surface3D::Surface3D(Q3DSurface *surface, DialogTransmitterProduct *dialog)
    : m_graph(surface), m_dialog(dialog), m_xmin(0.0),m_xmax(0.0),m_ymin(0.0),m_ymax(0.0),
      m_zmin(0.0),m_zmax(0.0)
{
    m_graph->setAxisX(new QValue3DAxis);
    m_graph->setAxisY(new QValue3DAxis);
    m_graph->setAxisZ(new QValue3DAxis);

    m_patternProxy = new QSurfaceDataProxy();
    m_patternSeries = new QSurface3DSeries(m_patternProxy);
    fillPatternProxy();
}

Surface3D::~Surface3D(){

}

void Surface3D::fillPatternProxy()
{
    float stepTheta = (sampleThetaMax - sampleThetaMin) / float(sampleCountTheta - 1);
    float stepPhy = (samplePhyMax - samplePhyMin) / float(sampleCountPhy - 1);
    float frequency = m_dialog->getFrequency();
    int row = m_dialog->getRow();
    int column = m_dialog->getColumn();
    double antennaDistance = m_dialog->getAntennaDistance();

    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    dataArray->reserve(sampleCountPhy);
    for (int i = 0 ; i < sampleCountPhy ; i++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(sampleCountTheta);
        // Keep values within range bounds, since just adding step can cause minor drift due
        // to the rounding errors.
        float phy = qMin(samplePhyMax, (i * stepPhy + samplePhyMin));
        int index = 0;
        for (int j = 0; j < sampleCountTheta; j++) {
            float theta = qMin(sampleThetaMax, (j * stepTheta + sampleThetaMin));
            double gain = MathematicalTransmitterProduct::computeGain(double(theta),double(phy),frequency,row,column,antennaDistance);
            float x = gain*qSin(phy*M_PI/180.0)*qCos(theta*M_PI/180.0);
            m_xmax = qMax(x,m_xmax);
            m_xmin = qMin(x,m_xmin);
            float y = gain*qCos(phy*M_PI/180.0);
            m_ymax = qMax(y,m_ymax);
            m_ymin = qMin(y,m_ymin);
            float z = gain*qSin(phy*M_PI/180.0)*qSin(theta*M_PI/180.0);
            m_zmax = qMax(z,m_zmax);
            m_zmin = qMin(z,m_zmin);
            (*newRow)[index++].setPosition(QVector3D(x, y, z));
        }
        *dataArray << newRow;
    }
    m_graph->axisX()->setRange(m_xmin-1.0, m_xmax+1.0);
    m_graph->axisY()->setRange(m_ymin-1.0, m_ymax+1.0);
    m_graph->axisZ()->setRange(m_zmin-1.0, m_zmax+1.0);
    m_patternProxy->resetArray(dataArray);
}

void Surface3D::enablePatternModel(bool enable)
{
    if (enable) {
        //! [3]
        m_patternSeries->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
        m_patternSeries->setFlatShadingEnabled(true);

        m_graph->axisX()->setLabelFormat("%.2f");
        m_graph->axisZ()->setLabelFormat("%.2f");
        m_graph->axisX()->setRange(m_xmin, m_xmax);
        m_graph->axisY()->setRange(m_ymin, m_ymax);
        m_graph->axisZ()->setRange(m_zmin, m_zmax);
        m_graph->axisX()->setLabelAutoRotation(30);
        m_graph->axisY()->setLabelAutoRotation(90);
        m_graph->axisZ()->setLabelAutoRotation(30);

        m_graph->addSeries(m_patternSeries);
        //! [3]

        //! [8]
        // Reset range sliders for Sqrt&Sin
        m_rangeMinX = m_xmin;
        m_rangeMinZ = m_zmin;
        m_stepX = (m_xmax - m_xmin) / float(sampleCountX - 1);
        m_stepZ = (m_zmax - m_zmin) / float(sampleCountZ - 1);
        m_axisMinSliderX->setMaximum(sampleCountX - 2);
        m_axisMinSliderX->setValue(0);
        m_axisMaxSliderX->setMaximum(sampleCountX - 1);
        m_axisMaxSliderX->setValue(sampleCountX - 1);
        m_axisMinSliderZ->setMaximum(sampleCountZ - 2);
        m_axisMinSliderZ->setValue(0);
        m_axisMaxSliderZ->setMaximum(sampleCountZ - 1);
        m_axisMaxSliderZ->setValue(sampleCountZ - 1);
        //! [8]
    }
}

void Surface3D::adjustXMin(int min)
{
    float minX = m_stepX * float(min) + m_xmin;

    int max = m_axisMaxSliderX->value();
    if (min >= max) {
        max = min + 1;
        m_axisMaxSliderX->setValue(max);
    }
    float maxX = m_stepX * max + m_xmin;

    setAxisXRange(minX, maxX);
}

void Surface3D::adjustXMax(int max)
{
    float maxX = m_stepX * float(max) + m_xmin;

    int min = m_axisMinSliderX->value();
    if (max <= min) {
        min = max - 1;
        m_axisMinSliderX->setValue(min);
    }
    float minX = m_stepX * min + m_xmin;

    setAxisXRange(minX, maxX);
}

void Surface3D::adjustZMin(int min)
{
    float minZ = m_stepZ * float(min) + m_zmin;

    int max = m_axisMaxSliderZ->value();
    if (min >= max) {
        max = min + 1;
        m_axisMaxSliderZ->setValue(max);
    }
    float maxZ = m_stepZ * max + m_zmin;

    setAxisZRange(minZ, maxZ);
}

void Surface3D::adjustZMax(int max)
{
    float maxX = m_stepZ * float(max) + m_zmin;

    int min = m_axisMinSliderZ->value();
    if (max <= min) {
        min = max - 1;
        m_axisMinSliderZ->setValue(min);
    }
    float minX = m_stepZ * min + m_zmin;

    setAxisZRange(minX, maxX);
}

//! [5]
void Surface3D::setAxisXRange(float min, float max)
{
    m_graph->axisX()->setRange(min, max);
}

void Surface3D::setAxisZRange(float min, float max)
{
    m_graph->axisZ()->setRange(min, max);
}

void Surface3D::changeTheme(int theme)
{
    m_graph->activeTheme()->setType(Q3DTheme::Theme(theme));
}
//! [6]

void Surface3D::setBlackToYellowGradient()
{
    //! [7]
    QLinearGradient gr;
    gr.setColorAt(0.0, Qt::black);
    gr.setColorAt(0.33, Qt::blue);
    gr.setColorAt(0.67, Qt::red);
    gr.setColorAt(1.0, Qt::yellow);

    m_graph->seriesList().at(0)->setBaseGradient(gr);
    m_graph->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleObjectGradient);
    //! [7]
}

void Surface3D::setGreenToRedGradient()
{
    QLinearGradient gr;
    gr.setColorAt(0.0, Qt::darkGreen);
    gr.setColorAt(0.5, Qt::yellow);
    gr.setColorAt(0.8, Qt::red);
    gr.setColorAt(1.0, Qt::darkRed);

    m_graph->seriesList().at(0)->setBaseGradient(gr);
    m_graph->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleObjectGradient);
}
