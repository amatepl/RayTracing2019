#include "interfererencepattern.h"

const int sampleCountX = 60;
const int sampleCountZ = 60;
const float sampleMin = -30.0;
const float sampleMax = 30.0f;

InterfererencePattern::InterfererencePattern(Q3DSurface *surface)
    : m_graph(surface)
{
    QFont font;
    font.setPointSize(50);
    m_graph->setAxisX(new QValue3DAxis);
    m_graph->axisX()->setTitleVisible(true);
    QString x_axe = QString("x/") + QChar(0x03BB);
    m_graph->axisX()->setTitle(x_axe);
    m_graph->setAxisY(new QValue3DAxis);
    m_graph->axisY()->setTitleVisible(true);
    QString y_axe = QString("|h| [dB]");
    m_graph->axisY()->setTitle(y_axe);
    m_graph->setAxisZ(new QValue3DAxis);
    m_graph->axisZ()->setTitleVisible(true);
    QString z_axe = QString("z/") + QChar(0x03BB);
    m_graph->axisZ()->setTitle(z_axe);
    m_graph->activeTheme()->setType(Q3DTheme::ThemeStoneMoss);
    m_graph->activeTheme()->setFont(font);

    m_impulseproxy = new QSurfaceDataProxy();
    m_impulseseries = new QSurface3DSeries(m_impulseproxy);
}

InterfererencePattern::~InterfererencePattern()
{
    delete m_graph;
}

void
InterfererencePattern::enableImpulseInterference(std::vector<double> impulse_r,double min, double max)
{
    m_impulse_r = impulse_r;
    fillImpulseProxy();
    m_impulseseries->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
    m_impulseseries->setFlatShadingEnabled(true);

    m_graph->axisX()->setLabelFormat("%.2f");
    m_graph->axisZ()->setLabelFormat("%.2f");
    m_graph->axisX()->setRange(sampleMin, sampleMax);
    m_graph->axisY()->setRange(min, max);
    m_graph->axisZ()->setRange(sampleMin, sampleMax);
    m_graph->axisX()->setLabelAutoRotation(30);
    m_graph->axisY()->setLabelAutoRotation(90);
    m_graph->axisZ()->setLabelAutoRotation(30);

    m_graph->addSeries(m_impulseseries);

    m_rangeMinX = sampleMin;
    m_rangeMinZ = sampleMin;
    m_stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
    m_stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);
    m_axisMinSliderX->setMaximum(sampleCountX - 2);
    m_axisMinSliderX->setValue(0);
    m_axisMaxSliderX->setMaximum(sampleCountX - 1);
    m_axisMaxSliderX->setValue(sampleCountX - 1);
    m_axisMinSliderZ->setMaximum(sampleCountZ - 2);
    m_axisMinSliderZ->setValue(0);
    m_axisMaxSliderZ->setMaximum(sampleCountZ - 1);
    m_axisMaxSliderZ->setValue(sampleCountZ - 1);

    QLinearGradient gr;
    gr.setColorAt(0.0, Qt::black);
    gr.setColorAt(0.33, Qt::blue);
    gr.setColorAt(0.67, Qt::red);
    gr.setColorAt(1.0, Qt::yellow);

    m_graph->seriesList().at(0)->setBaseGradient(gr);
    m_graph->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
}

void
InterfererencePattern::adjustXMin(int min)
{
    float minX = m_stepX * float(min) + m_rangeMinX;

    int max = m_axisMaxSliderX->value();
    if (min >= max) {
        max = min + 1;
        m_axisMaxSliderX->setValue(max);
    }
    float maxX = m_stepX * max + m_rangeMinX;

    setAxisXRange(minX, maxX);
}

void
InterfererencePattern::adjustXMax(int max)
{
    float maxX = m_stepX * float(max) + m_rangeMinX;

    int min = m_axisMinSliderX->value();
    if (max <= min) {
        min = max - 1;
        m_axisMinSliderX->setValue(min);
    }
    float minX = m_stepX * min + m_rangeMinX;

    setAxisXRange(minX, maxX);
}

void
InterfererencePattern::adjustZMin(int min)
{
    float minZ = m_stepZ * float(min) + m_rangeMinZ;

    int max = m_axisMaxSliderZ->value();
    if (min >= max) {
        max = min + 1;
        m_axisMaxSliderZ->setValue(max);
    }
    float maxZ = m_stepZ * max + m_rangeMinZ;

    setAxisZRange(minZ, maxZ);
}

void
InterfererencePattern::adjustZMax(int max)
{
    float maxX = m_stepZ * float(max) + m_rangeMinZ;

    int min = m_axisMinSliderZ->value();
    if (max <= min) {
        min = max - 1;
        m_axisMinSliderZ->setValue(min);
    }
    float minX = m_stepZ * min + m_rangeMinZ;

    setAxisZRange(minX, maxX);
}

void
InterfererencePattern::setAxisXRange(float min, float max)
{
    m_graph->axisX()->setRange(min, max);
}

void
InterfererencePattern::setAxisZRange(float min, float max)
{
    m_graph->axisZ()->setRange(min, max);
}

void
InterfererencePattern::fillImpulseProxy()
{
    float stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
    float stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);

    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    dataArray->reserve(sampleCountZ);
    int k = 0;
    for (int i = 0 ; i < sampleCountZ ; i++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(sampleCountX);
        // Keep values within range bounds, since just adding step can cause minor drift due
        // to the rounding errors.
        float z = qMin(sampleMax, (i * stepZ + sampleMin));
        int index = 0;
        for (int j = 0; j < sampleCountX; j++) {
            float x = qMin(sampleMax, (j * stepX + sampleMin));
            float y = m_impulse_r[k];
            k++;
            (*newRow)[index++].setPosition(QVector3D(x, y, z));
        }
        *dataArray << newRow;
    }

    m_impulseproxy->resetArray(dataArray);
}
